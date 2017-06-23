#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include "statistics.h"
#include "prog_opts_util.h"
#include "udp_server.h"
#include "wrapsock.h"

using namespace std;
using namespace std::chrono;

struct Serv_conf {
    int bytes_per_packet;
    int packets_per_response;
    int rate_request_to_response;
    std::atomic<uint32_t> total_recv_packets;
    std::atomic<uint64_t> total_recv_bytes;
    std::atomic<uint32_t> total_send_packets;
    std::atomic<uint64_t> total_send_bytes;
};

void serv_routine(vector<int> fd_set, Serv_conf *serv_conf);

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);
    cout << "program_options: \n";
    Print_variables_map(vm);
    cout << "\n\n" << endl;

    vector<int> fd_set;
    int server_number = 1;
    string server_host = vm["server_host"].as<string>();
    string server_port = vm["server_port"].as<string>();
    for (int i = 0; i < server_number; i++) {
	    int sockfd = Udp_server(server_host.c_str(), server_port.c_str(), NULL);
        fd_set.push_back(sockfd);
    } 

    Serv_conf serv_conf;
    serv_conf.bytes_per_packet = vm["bytes_per_packet"].as<int>();
    serv_conf.packets_per_response = vm["packets_per_response"].as<int>();
    serv_conf.rate_request_to_response = vm["rate_request_to_response"].as<int>();
    serv_conf.total_send_packets = 0;
    serv_conf.total_send_bytes = 0;
    serv_conf.total_recv_packets = 0;
    serv_conf.total_recv_bytes = 0;

    int thread_number = vm["thread_number"].as<int>();
    vector<thread> serv_threads;
    for (int i = 0; i < thread_number; i++) {
        std::thread serv_thread(serv_routine, fd_set, &serv_conf);
        serv_thread.detach();
        serv_threads.push_back(std::move(serv_thread));
    }  

    int statistics_interval = vm["statistics_interval"].as<int>();
    Statistics st1, st2;
    while (true) {
        st1.total_send_packets = serv_conf.total_send_packets;
        st1.total_send_bytes = serv_conf.total_send_bytes;
        st1.total_recv_packets = serv_conf.total_recv_packets;
        st1.total_recv_bytes = serv_conf.total_recv_bytes;
        st1.time_point = steady_clock::now();
        this_thread::sleep_for(seconds(statistics_interval));
        st2.total_send_packets = serv_conf.total_send_packets;
        st2.total_send_bytes = serv_conf.total_send_bytes;
        st2.total_recv_packets = serv_conf.total_recv_packets;
        st2.total_recv_bytes = serv_conf.total_recv_bytes;
        st2.time_point = steady_clock::now();
        print_statistics(st1, st2);
    }

    return 0;
}

void serv_routine(vector<int> fd_set, Serv_conf *serv_conf)
{
    const int MAX_EVENTS = 5;
    auto bytes_per_packet = serv_conf->bytes_per_packet;
    auto packets_per_response = serv_conf->packets_per_response;
    auto rate_request_to_response = serv_conf->rate_request_to_response; 
    const int BUF_SIZE = 8192;
    char      recv_buff[BUF_SIZE];

    string buffer(bytes_per_packet, 'Y');
    const void *send_buff = buffer.data();

    int    i, epfd, nready, sockfd, n;
    struct epoll_event  ev;
    struct epoll_event  evlist[MAX_EVENTS];

    epfd = Epoll_create(MAX_EVENTS);

    int nserver = fd_set.size();
    for (int i = 0; i < nserver; i++) {
        sockfd = fd_set[i];
        ev.data.fd = sockfd;
        ev.events = EPOLLIN; /* Only interested in input events */
        Epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    }

    int recv_packets = 0;
	struct sockaddr_storage	cliaddr;
	socklen_t	clilen;
	for ( ; ; ) {
		nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        for (i = 0; i < nready; i++) {
            if (evlist[i].events & EPOLLIN) {  /* net data in */
                sockfd = evlist[i].data.fd;

                clilen = sizeof(cliaddr);
                if ((n = recvfrom(sockfd, recv_buff, BUF_SIZE, MSG_DONTWAIT, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
                    continue;
                }

                serv_conf->total_recv_packets++;
                serv_conf->total_recv_bytes += n;
                recv_packets++;

                if ((recv_packets % rate_request_to_response) != 0) {
                    continue;
                } 

                for (int j = 0; j < packets_per_response; j++) {
                    if (bytes_per_packet == sendto(sockfd, send_buff, bytes_per_packet, MSG_DONTWAIT, (struct sockaddr *) &cliaddr, clilen)) {
                        serv_conf->total_send_packets++;
                        serv_conf->total_send_bytes += bytes_per_packet;
                    }
                }

                continue;
            }
        }
    }
}

