#include <thread>
#include <chrono>
#include <unistd.h>

extern "C" {
#include	"udp_server.h"
#include	"wrapunix.h"
#include    "wrapsock.h"
}

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen, int pipe_fd);

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	cliaddr;

	if (argc == 2)
		sockfd = Udp_server(NULL, argv[1], NULL);
	else if (argc == 3)
		sockfd = Udp_server(argv[1], argv[2], NULL);
	else
		err_quit("usage: daytimetcpsrv4 [ <host> ] <service or port>");

    int pipe_fds[2];
    Pipe(pipe_fds);

    std::thread echo(&dg_echo, sockfd, (SA *) &cliaddr, sizeof(cliaddr), pipe_fds[0]);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        write(pipe_fds[1], "x", 1);
    }

    return 0;
}
