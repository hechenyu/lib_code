extern "C" {
#include "wrapsock.h"
#include "wrapstdio.h"
#include "sock_ntop.h"
}

#include <unistd.h>

#include <unordered_map>
#include <iostream>
#include <string>

#define MAX_EVENTS 5 /* Maximum number of events to be returned from
                        a single epoll_wait() call */

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen, int pipe_fd)
{
	int			n;
	socklen_t	len;
	char		mesg[MAXLINE];
	char	    line[MAXLINE];

    int    i, epfd, nready;
    struct epoll_event  ev;
    struct epoll_event  evlist[MAX_EVENTS];

#ifdef	NOTDEF
    char                str[INET_ADDRSTRLEN];
#endif

    epfd = Epoll_create(MAX_EVENTS);

    ev.data.fd = pipe_fd;
    ev.events = EPOLLIN; /* Only interested in input events */
    Epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd, &ev);

    ev.data.fd = sockfd;
    ev.events = EPOLLIN; /* Only interested in input events */
    Epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

    std::unordered_map<std::string, int> cliaddr_pkt_map;
    cliaddr_pkt_map.reserve(100000);
    std::string str_cliaddr;

	for ( ; ; ) {
		nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        for (i = 0; i < nready; i++) {
#if NOTDEF
            printf(" fd=%d; events: %s%s%s%s%s\n", evlist[i].data.fd,
                    (evlist[i].events & EPOLLIN) ? "EPOLLIN " : "",
                    (evlist[i].events & EPOLLOUT) ? "EPOLLOUT " : "",
                    (evlist[i].events & EPOLLRDHUP) ? "EPOLLRDHUP " : "",
                    (evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
                    (evlist[i].events & EPOLLERR) ? "EPOLLERR " : "");
#endif

            if (evlist[i].data.fd == sockfd && evlist[i].events & EPOLLIN) {  /* net data in */
                len = clilen;
                n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

                ++cliaddr_pkt_map[Sock_ntop(pcliaddr, clilen)];
#ifdef	NOTDEF
                printf("recvfrom: %s, len: %d\n", Sock_ntop(pcliaddr, clilen), n);
#endif

                Sendto(sockfd, mesg, n, 0, pcliaddr, len);
                continue;
            }

            if (evlist[i].data.fd == pipe_fd && evlist[i].events & EPOLLIN) {  /* stdin data in */
                read(pipe_fd, line, MAXLINE);
                std::cout << "client map: \n";
                for (auto &item: cliaddr_pkt_map) {
                    std::cout << "[" << item.first << "]:" << item.second << '\n';
                }
                std::cout << "size: " << cliaddr_pkt_map.size() << "\n";
                std::cout << std::endl;
                continue;
            }
        }
    }
}
