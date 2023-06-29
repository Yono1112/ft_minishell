#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char **argv)
// {
// 	int	pfd[2];

// 	(void)argc;
// 	(void)argv;
// 	if (pipe(pfd) == -1)
// 		exit(EXIT_FAILURE);
// 	switch (fork())
// 	{
// 		case -1:
// 			exit(EXIT_FAILURE);
// 		case 0:
// 			if (close(pfd[0] == -1))
// 				exit(EXIT_FAILURE);
// 			if (pfd[1] != STDOUT_FILENO)
// 			{
// 				if (dup2(pfd[1], STDOUT_FILENO) == -1)
// 					exit(EXIT_FAILURE);
// 				if (close(pfd[1] == -1))
// 					exit(EXIT_FAILURE);
// 			}
// 			execlp("ls", "ls", (char *) NULL);
// 			exit(EXIT_FAILURE);
// 		default:
// 			break ;
// 	}
// 	switch (fork())
// 	{
// 		case -1:
// 			exit(EXIT_FAILURE);
// 		case 0:
// 			if (close(pfd[1]) == -1)
// 				exit(EXIT_FAILURE);
// 			if (pfd[0] != STDIN_FILENO)
// 			{
// 				if (dup2(pfd[0], STDIN_FILENO) == -1)
// 					exit(EXIT_FAILURE);
// 				if (close(pfd[0] == -1))
// 					exit(EXIT_FAILURE);
// 			}
// 			execlp("wc", "wc", "-l", (char *) NULL);
// 			exit(EXIT_FAILURE);
// 		default:
// 			break ;
// 	}
// 	if (close(pfd[0] == -1))
// 		exit(EXIT_FAILURE);
// 	if (close(pfd[1] == -1))
// 		exit(EXIT_FAILURE);
// 	if (wait(NULL) == -1)
// 		exit(EXIT_FAILURE);
// 	if (wait(NULL) == -1)
// 		exit(EXIT_FAILURE);
// 	exit(EXIT_SUCCESS);
// }

#include <sys/wait.h>

void	errExit(char *str)
{
	printf("error: %s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		errExit("pipe");
	switch (fork())
	{
	case -1:
		errExit("fork");
	case 0:
		if (close(pfd[0]) == -1)
			errExit("close 1");
		if (pfd[1] != STDOUT_FILENO)
		{
			if (dup2(pfd[1], STDOUT_FILENO) == -1)
				errExit("dup2 1");
			if (close(pfd[1]) == -1)
				errExit("close 2");
		}
		execlp("ls", "ls", (char *) NULL);
		errExit("execlp ls");
	default:
		break;
	}
	switch (fork())
	{
	case -1:
		errExit("fork");
	case 0:
		if (close(pfd[1]) == -1)
			errExit("close 3");
		if (pfd[0] != STDIN_FILENO)
		{
			if (dup2(pfd[0], STDIN_FILENO) == -1)
				errExit("dup2 2");
			if (close(pfd[0]) == -1)
				errExit("close 4");
		}
		execlp("wc", "wc", "-l", (char *) NULL);
		errExit("execlp wc");
	default:
		break;
	}
	if (close(pfd[0]) == -1)
		errExit("close 5");
	if (close(pfd[1]) == -1)
		errExit("close 6");
	if (wait(NULL) == -1)
		errExit("wait 1");
	if (wait(NULL) == -1)
		errExit("wait 2");
	(void)argc;
	(void)argv;
	exit(EXIT_SUCCESS);
}
