#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int	num_dead;
	pid_t	child_pid;
	int	j;

	setbuf(stdout, NULL);
	for (j = 1; j < argc; j++)
	{
		switch (fork())
		{
		case -1:
			exit(EXIT_FAILURE);
		case 0:
			printf("child %d started with PID %ld , sleeping %s"
				"second\n", j, (long)getpid(), argv[j]);
			sleep(j);
			exit(EXIT_SUCCESS);
		default:
			break;
		}
	}
	num_dead = 0;
	for (;;)
	{
		child_pid = wait(NULL);
		if (child_pid == -1)
		{
			if (num_dead == argc)
			{
				printf("No more children - bye\n");
				exit(EXIT_SUCCESS);
			}
			// else
			// {
			// 	printf("error wait");
			// 	exit(EXIT_FAILURE);
			// }
		}
		num_dead++;
		printf("wait() returned child PID %ld (num_dead=%d)\n", (long)child_pid, num_dead);
	}
}