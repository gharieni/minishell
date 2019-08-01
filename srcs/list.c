#include <minishell.h>

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
		ft_strdel(&begin->content);
		ft_strdel(&begin->var);
		free(begin);
		begin = NULL;
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


