#include "minishell.h"

void    handler(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		signal(SIGINT, handler);
	}
}

void    signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		printf("*•••••••  gmelek> ");
			signal(SIGINT, signal_handler);
	}
}


