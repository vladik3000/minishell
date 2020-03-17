#include <stdio.h>

int main(int ac, char **av, char **ev)
{
	int i = 0;
	printf("HELLO\n");
	while (ev[i])
	{
		printf("%s\n", ev[i]);
		i++;
	}
	printf("BYE\n");
	return (0);
}
