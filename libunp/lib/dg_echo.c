#include	"dg_echo.h"

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int			n;
	socklen_t	len;
	char		mesg[MAXLINE];

#ifdef	NOTDEF
    char                str[INET_ADDRSTRLEN];
#endif

	for ( ; ; ) {
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

#ifdef	NOTDEF
			printf("new client: %s, port %d\n",
					Inet_ntop(AF_INET, &pcliaddr->sin_addr, str, sizeof(str)),
					ntohs(pcliaddr->sin_port));
#endif

		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
