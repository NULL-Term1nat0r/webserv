#include <iostream>
#include <signal.h>
#include <unistd.h>


class catchSignal
{
	public:
		static	bool	exitLoop; 
		catchSignal() { std::cout << "catchSignal constructor" << std::endl; }
		~catchSignal() { std::cout << "catchSignal destructor" << std::endl; };
		catchSignal(const catchSignal &other);
		catchSignal &operator=(const catchSignal &other);
};

void	ctrlC(int status) //close all connections and sockets
{
	if (status == SIGINT) {
		catchSignal::exitLoop = false;
		std::cout << std::endl << "webserver closed." << std::endl;
	}
}

bool catchSignal::exitLoop = true;

void	getSignals(void)
{
	signal(SIGINT, &ctrlC);
	signal(SIGQUIT, SIG_IGN);
}

int main()
{
	catchSignal a;
	catchSignal *b[2];
	int i = 0;
	while(catchSignal::exitLoop) {
		getSignals();
		if (i == 0)
			b[0] = new catchSignal();
		i++;
		catchSignal::exitLoop = false;
	}
	delete b[0];
}