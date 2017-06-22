#include "prog_opts_util.h"

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);
    Print_variables_map(vm);

	int					sockfd;

#if 0
	if (argc != 3)
		err_quit("usage: daytimetcpcli <hostname/IPaddress> <service/port#>");

	sockfd = Udp_connect(argv[1], argv[2]);

	exit(0);
#endif

    return 0;
}
