#include "minishell.h"

void    handler(int sign)
{
	if (sign == SIGINT)
	{
			ft_putstr("\n");
			signal(SIGINT, handler);
	}
}

void    signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		ft_putstr("\n");
		ft_putstr("•••••••  gmelek> ");
		signal(SIGINT, signal_handler);
	}
}


