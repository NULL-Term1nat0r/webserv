
#include "unistd.h"
#include <sys/wait.h>
#include <string>
#include <iostream>

bool	packageInstalled()
{
	int	exitCode;
	std::string	cgiScript;
	if (cgiScript != ".py")  
		exitCode = std::system("python3 --version");
	else
		exitCode = std::system("php --version");
	if (exitCode != 0)
		return false;
	return true;
}

// bool fileOpen

//check which filextension also if wrong file extension change in parsing part



void	executeCgi()
{
	int fd[2];
	if (pipe(fd) == -1) {
		//pipe failed
	}
	pid_t	childId;
	childId = fork();
	if (childId == -1)
		//error
	if (childId == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			//error
		// if (.py)
		// 	execve("/usr/bin/python", cmd & pathToCgi, env var); //cmd to run python // env = url and 0
		// else
		// 	execve("/usr/bin/php", cmd & pathToCgi, env var); //cmd to run php // env = url and 0
		close(fd[1]);
		exit(1);
	}
	else {
		close(fd[1])
		if (dup2(fd[0], STDIN_FILENO) == -1)
			//error
		close(fd[0]);
		// if (alarm(scriptTimeout) == 0) { //probably not allowed
		// 	kill(childPID, SIGTERM);
		// }
		waitpid(childId, NULL, 0);
	}
}