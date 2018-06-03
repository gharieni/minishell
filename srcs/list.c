#include <minishell.h>

void print_list(t_list *l)
{
	while(l)
	{
		printf(" %s  \n",(char*)l->content);
		l = l->next;
	}
}

int		my_find_elm_eq_in_list(t_list *begin, void *data_ref)
{
  while (begin && ft_memcmp(begin->content, data_ref,
			ft_strlen(data_ref)))
    {
      begin = begin->next;
    }
  if (begin)
    return (1);
  else
    return (0);
}

void	my_find_list_del(t_list **list, void *data_ref)
{
	t_list *begin;
	t_list *tmp;

	begin = *list;
  while (begin && ft_memcmp(begin->content, data_ref,
			ft_strlen(data_ref)))
    {
		tmp = begin;
		begin = begin->next;
    }
  if (begin)
  {
	printf ("yoooooooooooooooooooooooooooooo %s\n",data_ref);
	  tmp->next = begin->next;
		//free(begin->content);
		//begin->content = NULL;
		begin = NULL;
		free(begin);
		//begin = tmp;
	 }
 	printf("_________________________________ \n\n");
	print_list(*list);
	printf("_________________________________ \n\n");
}


t_list		*ft_create_elem(void *data)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (list)
	{
		list->content = data;
		list->next = NULL;
	}
	return (list);
}

void my_list_add(void* data, t_list	**begin_list)
{
	t_list* list;


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

t_list* list_check_add(void* data, t_list* list)
{
	if(!my_find_elm_eq_in_list(list,data))
		my_list_add(data,&list);
	return list;
}



t_list *my_params_in_list(char **av)
{
	t_list* l;
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

void	ft_list_clear(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*list;

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

