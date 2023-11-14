#include <iostream>
#include <signal.h>
#include <unistd.h>

// for cgi custom signals could be used
//cgi has to end but also main process
void	ctrlC(int status) //close all connections and sockets
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

// void	ctrlCChild(int status)
// {
// 	if (status == SIGINT)
// 	{
	
// 	}
// 	if (status == SIGQUIT)
// 	{
		
// 	}
// }

// void	getSignalsChild(void)
// {
// 	signal(SIGINT, &ctrlCChild);
// 	signal(SIGQUIT, &ctrlCChild);
// }


int main()
{
	while(1) {
		getSignals();
	}
}