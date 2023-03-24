#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define CHILD_PROCESS 0

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*cmd = argv[1];
	char	*args[] = {cmd, NULL};
	int		status;
	// char	**args;

	if (argc != 2)
		return (1);
	// args = malloc(sizeof(char *) * (argc + 1));
	// for (int i = 0; i < argc; i++){
	// 	args[i] = argv[i];
	// }
	// args[argc] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	else if (pid == CHILD_PROCESS)
	{
		execve(cmd, args, NULL);
		perror("execve error:");
		exit(EXIT_FAILURE);
	}
	else
	{
		pid = wait(&status);
		if (pid == -1)
		{
			perror("wait error:");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		else
			printf("Child process exited abnormally\n");
	}
	// free(args);
	return (0);
}
