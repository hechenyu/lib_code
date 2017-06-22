#include <vector>
#include <thread>
#include <chrono>
#include "prog_opts_util.h"
#include "udp_connect.h"
#include "wrapsock.h"

using namespace std;

struct Send_conf {
    int bytes_per_packet;
    int packets_per_loop;
    int sleep_per_loop;
    std::atomic<int> total_send_packets;
};

struct Recv_conf {
    int bytes_per_packet;
    std::atomic<int> total_recv_packets;
};

static void send_rountine(vector<int> fd_set, Send_conf *send_conf);
static void recv_rountine(vector<int> fd_set, Recv_conf *recv_conf);

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);
    Print_variables_map(vm);

    vector<int> fd_set;
    int client_number = vm["client_number"].as<int>();
    string server_host = vm["server_host"].as<string>();
    string server_port = vm["server_port"].as<string>();
    for (int i = 0; i < client_number; i++) {
	    int sockfd = Udp_connect(server_host.c_str(), server_port.c_str());
        fd_set.push_back(sockfd);
    } 

    Send_conf send_conf;
    send_conf.bytes_per_packet = vm["bytes_per_packet"].as<int>();
    send_conf.packets_per_loop = vm["packets_per_loop"].as<int>();
    send_conf.sleep_per_loop = vm["sleep_per_loop"].as<int>();
    send_conf.total_send_packets = 0;

    Recv_conf recv_conf;
    recv_conf.bytes_per_packet = vm["bytes_per_packet"].as<int>();
    recv_conf.total_recv_packets = 0;

    std::thread send_thread(send_rountine, fd_set, &send_conf);
    send_thread.detach();

    std::thread recv_thread(recv_rountine, fd_set, &recv_conf);
    recv_thread.detach();

    return 0;
}

void send_rountine(vector<int> fd_set, Send_conf *send_conf)
{
    auto bytes_per_packet = send_conf->bytes_per_packet;
    auto packets_per_loop = send_conf->packets_per_loop;
    auto sleep_per_loop = send_conf->sleep_per_loop;

    string buffer(bytes_per_packet, 'X');
    const void *buff = buffer.data();

    int nclient = fd_set.size();
    for ( ; ; ) {
        for (int i = 0; i < nclient; i++) {
            for (int j = 0; i < packets_per_loop; j++) {
                if (bytes_per_packet == send(fd_set[i], buff, bytes_per_packet, MSG_DONTWAIT)) {
                    send_conf->total_send_packets++;
                }
            }
        }

        this_thread::sleep_for(chrono::microseconds(sleep_per_loop));
    }
}

void recv_rountine(vector<int> fd_set, Recv_conf *recv_conf)
{
    const int MAX_EVENTS = 5;
    int     bytes_per_packet = recv_conf->bytes_per_packet; 
    char    *buff = new char[bytes_per_packet+1]; 

    int    i, epfd, nready, sockfd;
    struct epoll_event  ev;
    struct epoll_event  evlist[MAX_EVENTS];

    epfd = Epoll_create(MAX_EVENTS);

    int nclient = fd_set.size();
    for (int i = 0; i < nclient; i++) {
        sockfd = fd_set[i];
        ev.data.fd = sockfd;
        ev.events = EPOLLIN; /* Only interested in input events */
        Epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    }

	for ( ; ; ) {
		nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        for (i = 0; i < nready; i++) {
            if (evlist[i].events & EPOLLIN) {  /* net data in */
                sockfd = evlist[i].data.fd;
                if (bytes_per_packet == recv(sockfd, buff, bytes_per_packet, MSG_DONTWAIT)) {
                    recv_conf->total_recv_packets++;
                }
                continue;
            }
        }
    }
}
