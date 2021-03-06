#include "minishell.h"

int	ft_strisalnum(char *s)
{
	while (*s)
	{
		if (ft_isalnum(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

t_env		*my_unsetenv(char *var,char *val,t_env **l)
{
	char *str;
	char *tmp;

	if(!var)
		return *l;
	tmp = ft_strjoin(var,"=");
	str = ft_strjoin(tmp,val);
	my_find_list_del(l, str);
	ft_strdel(&tmp);
	ft_strdel(&str);
	return *l;
}

int setenv_err(char *var)
{
	if (ft_isalpha(var[0]) == 0)
	{
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
		return 1;
	}
	if (ft_strisalnum(var) == 0)
	{
		ft_putstr_fd("setenv: Variable name ", 2);
		ft_putendl_fd("must contain alphanumeric characters.", 2);
		return 1;
	}
return 0;
}

t_env		*my_setenv(char *var,char *val,t_env *l)
{
	char *str;
	char *tmp;
	if(!setenv_err(var))
		if (!modif_env(&l,val,var))
		{
			tmp = ft_strjoin(var,"=");
			str = ft_strjoin(tmp,val);
			l = list_check_add(str,l);
			ft_strdel(&str);
			ft_strdel(&tmp);
		}
	return l;
}

int   modif_env(t_env **list,char *var, void *data_ref)
{
	char	*str;
	char	*old;
	t_env	 *begin;
	begin = *list;
	unsigned int i;

	i = 0;
	while (begin &&
			ft_memcmp(begin->content, data_ref, ft_strlen(data_ref)) != 0)
		begin = begin->next;
	i = ft_strlen(data_ref);
	if (begin && ((unsigned char*)begin->content)[i] == '=')
	{
		data_ref = ft_strjoin(data_ref,"=");
		old = data_ref;
		str = ft_strjoin(data_ref,var);
		ft_strdel(&old);
		ft_strdel(&begin->content);
		begin->content = str;
		return 1;
	}
	return 0;
}
