#include "minishell.h"

void    ft_freestrarr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		if(!arr[i])
			return ;
		free(*(arr + i));
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void free_list(t_env **l)
{
	t_env* tmp;
	while(*l)
	{
		tmp = *l;
		ft_strdel(&tmp->var);
		ft_strdel(&tmp->content);
		*l = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}
