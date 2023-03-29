#include <stdio.h>

int main(void)
{
	char* operators[] = {"0", "11", "22"};

	for (size_t i = 0; i < sizeof(operators) / sizeof(*operators); i++)
		printf("operators[%zu]:%s, sizeof(operators):%zu, sizeof(*operators):%zu, sizeof(operators) / sizeof(*operators):%zu\n",
			i, operators[i], sizeof(operators), sizeof(*operators), sizeof(operators) / sizeof(*operators));
	return (0);
}
