#include <vector>
#include <thread>
#include <chrono>
#include "prog_opts_util.h"
#include "udp_connect.h"

using namespace std;

struct Send_conf {
    int bytes_per_packet;
    int packets_per_loop;
    int sleep_per_loop;
    std::atomic<int> total_send_packets;
};

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
