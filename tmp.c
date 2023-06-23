#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	if (chdir("/etccc") == -1)
		perror(NULL);

	errno = ENOMEM;
	perror(NULL);

	errno = EBADARCH;
	perror(NULL);
	strerror(ENOMEM);
}
