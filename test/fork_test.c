#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int idata = 100;

int	main(void)
{
	int		istack = 100;
	pid_t	child_pid;

	switch (child_pid = fork())
	{
		case -1:
			exit(EXIT_FAILURE);
		case 0:
			printf("child process start\n");
			idata *= 2;
			istack *= 2;
			break ;
		default:
			printf("parent process start\n");
			sleep(1);
			break ;
	}
	printf("PID = %ld %s idata = %d istack = %d \n", (long)getpid(),
		(child_pid == 0) ? "child" : "parent", idata, istack);
	exit(EXIT_SUCCESS);
}
