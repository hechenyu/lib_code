#include "prog_opts_util.h"
#include <string>
#include <fstream>

using namespace std;
using namespace boost::program_options;

variables_map Parse_command_line(int argc, char *argv[])
{
    options_description desc("udp_stree_client");

    string filename;
    desc.add_options()
        ("help,h", "produce help message")
        ("config_file,f", value<string>(&filename)->default_value(""), "config file")
        ("client_number", value<int>()->default_value(1), "number of client")
        ("server_address", value<string>()->default_value("[127.0.0.1:9999]"), "server address that client to connect")
        ("bytes_per_packet", value<int>()->default_value(500), "send packet size, bytes")
        ("packets_per_loop", value<int>()->default_value(1), "send packet number per time")
        ("sleep_per_loop", value<int>()->default_value(0), "sleep us per send loop")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (!filename.empty()) {
        ifstream ifs(filename);
        store(parse_config_file(ifs, desc, true), vm);
    }

    return vm;
}

