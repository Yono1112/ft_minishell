#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	main(void)
{
	int	fd_in, fd_out, fd_err;
	ssize_t	nread;
	char	buf[BUFSIZ];

	fd_in = open("log/input.txt", O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	fd_out = open("log/output.txt", O_WRONLY, 0644);
	if (fd_out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	fd_err = open("log/error.txt", O_WRONLY, 0644);
	if (fd_err == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_err, STDERR_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	while ((nread = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
	{
		if (write(STDOUT_FILENO, buf, nread) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		if (write(STDERR_FILENO, "error", 5) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
	close(fd_in);
	close(fd_out);
	close(fd_err);
	return (EXIT_SUCCESS);
}
