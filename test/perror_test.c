#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int	main(void)
{
	FILE *fp;

	fp = fopen("not_exit_file.txt", "r");
	if (fp == NULL)
	{
		perror("year!");
		exit(EXIT_FAILURE);
	}
	return (0);
}
