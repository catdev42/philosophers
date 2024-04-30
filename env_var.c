#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int i = 0;
	while (env[i])
	{
		printf("%i:::     %s \n", i, env[i]);
		i++;
	}
	return (0);
}