#include <minishell.h>

void print_list(t_env *l)
{
	while(l)
	{
		l = l->next;
		ft_putendl(l->content);
	}
}

int		my_find_elm_eq_in_list(t_env *begin, void *data_ref)
{
  while (begin && ft_memcmp(begin->content, data_ref,
			ft_strlen(data_ref)))
      begin = begin->next;
  if (begin)
    return (1);
  else
    return (0);
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

void	my_find_list_del(t_env **list, void *data_ref)
{
	t_env *begin;
	t_env *tmp;

	begin = *list;
  while (begin && ft_memcmp(begin->content, data_ref,
			ft_strlen(data_ref)))
    {
		tmp = begin;
		begin = begin->next;
    }
  if (begin)
  {
	  tmp->next = begin->next;
		//free(begin->content);
		//begin->content = NULL;
		begin = NULL;
		free(begin);
		//begin = tmp;
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

void my_list_add(void* data, t_env	**begin_list)
{
	t_env* list;


	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_elem(data);
	}
	else
		*begin_list = ft_create_elem(data);
}

t_env* list_check_add(void* data, t_env* list)
{
	if(!my_find_elm_eq_in_list(list,data))
		my_list_add(data,&list);
	return list;
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

