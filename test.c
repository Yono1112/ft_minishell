#include <string.h>
#include <stdio.h>

int main(void)
{
	printf("%s\n", strdup(""));
	printf("%s\n", strdup("a"));
}
