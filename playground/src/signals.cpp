
#include <signal.h>

void	ctrlC(int status) //close all connections, for cgi custom signals could be used
{
	if (status == SIGINT) {
		std::cout << std::endl << "webserver closed." << std::endl;
		exit(1);
	}
}

void	getSignals(void)
{
	signal(SIGINT, &ctrlC);
	signal(SIGQUIT, SIG_IGN);
}
