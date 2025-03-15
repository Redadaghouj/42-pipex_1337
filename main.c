#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
    if (*envp == NULL)
    {
        printf("envp = NULL\n");
        return (0);
    }
    int i = 0;
	while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }
	return (0);
}