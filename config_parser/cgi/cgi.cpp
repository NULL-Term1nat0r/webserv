
#include "unistd.h"
#include <sys/wait.h>

void	executeCgi()
{
	//open file -> check if opened and not empty
	//check which filextension

	int fd[2];
	if (pipe(fd) == -1) {
		//pipe failed
	}
	pid_t	childId;
	childId = fork();
	if (childId == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			//error
		execve(path to cmd, cmd & pathToCgi, env var);
		close(fd[1]);
	}
	else {
		close(fd[1])
		if (dup2(fd[0], STDIN_FILENO) == -1)
			//error
		close(fd[0]);
		waitpid(childId, NULL, 0);
	}
}