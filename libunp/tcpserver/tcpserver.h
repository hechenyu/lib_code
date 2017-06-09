#ifndef __unp_tcpserver_h
#define __unp_tcpserver_h

namespace health_check {

class TcpConnectionHandler {
public:
    virtual void setup(int sockfd) = 0;     // when accept and new connection
    virtual int handle(int sockfd) = 0;     // when have data to read for an connection, 
                                            // return len to read, < 0 is error, 0 is EOF, > 0 is have data
};


class TcpServer {   // is not thread safe
public:
    TcpServer();
    ~TcpServer();

    bool add_handler(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler);
    std::shared_ptr<TcpConnectionHandler> remove_handler(const std::string &listen_host, int listen_port);
    bool clear_all_handler();   // if tcpserver is running, then return false.

    bool is_running();
    void start();
    void stop();
 
private:
    class Impl;
    Impl *impl;
};

}   // namespace health_check 

#endif
