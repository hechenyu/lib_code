/* include fig01 */
#include "tcpserver.h"

int
main(int argc, char **argv)
{
#if 0
	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], NULL);
	else
		err_quit("usage: daytimetcpsrv4 [ <host> ] <service or port>");
#endif

    TcpServer tcpserver;

}
/* end fig02 */
