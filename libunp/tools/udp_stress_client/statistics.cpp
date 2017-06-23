#include "statistics.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

void print_statistics(const Statistics &begin, const Statistics &end)
{
    system_clock::time_point now = system_clock::now();
    std::time_t tt = system_clock::to_time_t(now);
    cout << "time: " << ctime(&tt);

    duration<double> time_span = duration_cast<duration<double>>(end.time_point - begin.time_point);
    cout << "time_span: " << time_span.count() << " seconds\n";

    int total_send_packets = end.total_send_packets - begin.total_send_packets;
    cout << "total_send_packets: " << total_send_packets << '\n';  

    int total_send_bytes = end.total_send_bytes - begin.total_send_bytes;
    cout << "total_send_bytes: " << total_send_bytes << '\n';  

    int total_recv_packets = end.total_recv_packets - begin.total_recv_packets;
    cout << "total_recv_packets: " << total_recv_packets << '\n';  

    int total_recv_bytes = end.total_recv_bytes - begin.total_recv_bytes;
    cout << "total_recv_bytes: " << total_recv_bytes << '\n';  

    double send_pps = total_send_packets / time_span.count();
    double send_bps = total_send_bytes / time_span.count() / 1000000 * 8;
    cout << "send pps: " << send_pps << " packet/second\n";
    cout << "send bps: " << send_bps << " MBit/s\n";

    double recv_pps = total_recv_packets / time_span.count();
    double recv_bps = total_recv_bytes / time_span.count() / 1000000 * 8;
    cout << "recv pps: " << recv_pps << " packet/second\n";
    cout << "recv bps: " << recv_bps << " MBit/s\n";
    cout << "\n\n" << endl;
}
