#include <unistd.h>

int	main(void)
{
	write(1, "hello\n", 6);
	write(2, "error\n", 6);
	return (0);
}
