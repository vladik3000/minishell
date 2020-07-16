
#include <stdio.h>

int main(int ac, char **av, char **environ)
{
	int i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
