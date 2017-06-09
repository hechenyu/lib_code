#include "tcpserver.h"
#include "unp.h"

namespace health_check {

class TcpServer::Impl {
private:
    typedef std::tuple<std::string, int> addr_type;
    std::map<addr_type, int> addr2fd_map_;                                                      // map: listen_addr -> listenfd
    std::unordered_map<int, std::shared_ptr<TcpConnectionHandler> handler> fd2handler_map_;     // map: listenfd -> handler
    std::shared_ptr<std::thread> select_thread_;                                                // thread of run select loop
    int pipe_for_add_[2];                                                                       // notify add fd to thread
    int pipe_for_remove_[2];                                                                    // notify remove fd to thread
    int pipe_for_cancel_[2];                                                                    // notify cancel to thread

public:
    Impl()
    {
        Socketpair(AF_LOCAL, SOCK_DGRAM, 0, pipe_for_add_);
        Socketpair(AF_LOCAL, SOCK_DGRAM, 0, pipe_for_remove_);
        Pipe(pipe_for_cancel_);
    }

    ~Impl()
    {
        stop();
        clear_all_handler();
        close(pipe_for_add_[0]);
        close(pipe_for_add_[1]);
        close(pipe_for_remove_[0]);
        close(pipe_for_remove_[1]);
        close(pipe_for_cancel_[0]);
        close(pipe_for_cancel_[1]);
    }

    bool add_handler(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler)
    {
        auto listenfd = create_socket_and_insert_to_map(listen_host, listen_port, handler);
        if (listenfd < 0) {
            return false;
        }

        if (is_running()) {
            notify_add_to_fdset(listenfd);
        }
        return true;
    }

    std::shared_ptr<TcpConnectionHandler> remove_handler(const std::string &listen_host, int listen_port)
    {
        int listenfd;
        std::shared_ptr<TcpConnectionHandler> handler;
        std::tie(listenfd, handler) = find_and_remove_from_map(listen_host, listen_port);
        if (listenfd < 0) {
            return std::shared_ptr<TcpConnectionHandler>();
        }

        if (is_running()) {
            notify_remove_from_fdset(listenfd);
        }
        return handler;
    }

    bool clear_all_handler()
    {
        if (is_running()) {
            return false;
        }

        for (auto &item : fd2handler_map_) {
            close(item.first);
        }

        addr2fd_map_.clear();
        fd2handler_map_.clear();
        return true;
    }
 
    bool is_running()
    {
        return select_thread_ != nullptr;
    }

    void start()
    {
        if (is_running()) {
            return;
        }

        std::set<int> listenfds;
        for (auto &item : fd2handler_map_) {
            listenfds.insert(item.first);
        }

        select_thread_.reset(new std::thread(this, &TcpServer::Impl::select_routine, listenfds));
    }

    void stop()
    {
        if (!is_running()) {
            return;
        }

        notify_cancel_thread();
        select_thread_->join();
    }

private:
    int create_socket_and_insert_to_map(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler)
    {
        auto listen_addr = addr_type(listen_host, listen_port);
        if (addr2fd_map_.count(listen_addr)) {
            // already have handler for this listen addr
            return -1;
        }

		auto listenfd = tcp_listen(listen_host, listen_port, NULL);
        if (listenfd < 0) {
            // listen fail
            return -1;
        }

        addr2fd_map_[listen_addr] = listenfd;
        fd2handler_map_[listenfd] = handler;

        return listenfd;
    }

    std::tuple<int, std::shared_ptr<TcpConnectionHandler>> find_and_remove_from_map(const std::string &listen_host, int listen_port)
    {
        auto listen_addr = addr_type(listen_host, listen_port);
        if (addr2fd_map_.count(listen_addr)) {
            return std::make_tuple(-1, std::shared_ptr<TcpConnectionHandler>());
        }
        
        auto listenfd = addr2fd_map_[listen_addr];
        auto handler = fd2handler_map_[listenfd];

        addr2fd_map_.remove(listen_addr);
        fd2handler_map_.remove(listenfd);

        return std::make_tuple(listenfd, handler);
    }

    int recv_add_to_fdset()
    {
        char buf[128] = { 0 };
        auto n = read(pipe_for_add_[0], buf, sizeof buf);
        if (n <= 0) {
            return -1;
        }

        return atoi(buf);
    }

    int recv_remove_to_fdset()
    {
        char buf[128] = { 0 };
        auto n = read(pipe_for_remove_[0], buf, sizeof buf);
        if (n <= 0) {
            return -1;
        }

        return atoi(buf);
    }

    void notify_add_to_fdset(int listenfd)
    {
        auto str = std::to_string(listenfd);
        Write(pipe_for_add_[1], str.data(), str.size());
    }

    void notify_remove_from_fdset(int listenfd)
    {
        auto str = std::to_string(listenfd);
        Write(pipe_for_remove_[1], str.data(), str.size());
    }

    void notify_cancel_thread()
    {
        Write(pipe_for_cancel_[1], "C", 1);
    }

    bool is_recv_cancel()
    {
        char c;
        auto n = read(pipe_for_cancel_[0], c, 1); 
        if (n <= 0)
            return false;

        return true;
    }

    int init_fdset(fd_set *fdset, std::set<int> listenfds)
    {
        FD_ZERO(fdset);
        int maxfd = -1;

        FD_SET(pipe_for_add_[0], fdset);
        maxfd = std::max(pipe_for_add_[0], maxfd);

        FD_SET(pipe_for_remove_[0], fdset);
        maxfd = std::max(pipe_for_remove_[0], maxfd);

        FD_SET(pipe_for_cancel_[0], fdset);
        maxfd = std::max(pipe_for_cancel_[0], maxfd);

        for (auto fd : listenfds) {
            FD_SET(fd, fdset);
            maxfd = std::max(fd, maxfd);
        }

        return maxfd;
    }

    void select_routine(std::set<int> listenfds)
    {
        socklen_t                clilen;
        struct sockaddr_storage  cliaddr;

        FD_SET allset;
        auto maxfd = init_allset(&allset, listenfds);

        std::unordered_map<int, std::shared_ptr<TcpConnectionHandler> handler> connfd_map;

        for ( ; ; ) {
            FD_SET rset = allset;

            auto nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

            for (auto listenfd : listenfds) {
                if (FD_ISSET(listenfd, &rset)) {
                    clilen = sizeof(cliaddr);
                    auto connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
                    printf("new client: %s\n", Sock_ntop((struct sockaddr *) &cliaddr, clilen));

                    FD_SET(connfd, &allset);
                    maxfd = std::max(connfd, maxfd);

                    connfd_map.emplace(connfd, fd2handler_map_[listenfd]);
                    connfd_map[connfd]->setup(connfd);

                    if (--nready <= 0)
                        break;
                }
            }

            if (nready <= 0)
                continue;
        }

    }
};

}   // namespace health_check 

