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

char *add_var(char *str)
{
	char	*new;
	int		i;
	
	i = 0;
	while(str[i] != '=')
		i++;
	new = (char*)malloc(i + 1);
	new = strncpy(new,str,i);
	new[i] = '\0';
	return new;
}

t_env		*ft_create_elem(void *data)
{
	t_env	*list;

	list = (t_env*)malloc(sizeof(t_env));
	if (list)
	{
		list->var = add_var(data);
		list->content =ft_strdup(data);
		list->next = NULL;
	}
	return (list);
}

t_env *my_params_in_list(char **av)
{
	t_env* l;
	int i;

	i = 0;
	l = 0;
	while(av[i])
	{
		my_list_add(av[i], &l);
		i = i + 1;
	}
	return (l);
}
