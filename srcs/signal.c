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

void print_list(t_env *l)
{
	while(l)
	{
		ft_putendl(l->content);
		l = l->next;
	}
}

int	list_count (const t_env *list)
{
	int i;
	
	i = 0;
	if (list)
	while (list)
	{
		i++;
		list = list->next;
	}
	return i;
}

void	ft_env_clear(t_env **begin_list)
{
	t_env	*tmp;
	t_env	*list;

	list = *begin_list;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}
}
