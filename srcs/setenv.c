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

char *my_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if(ft_strncmp(env[i],"PATH=",5) == 0)
			return ((char*)env[i] + 5);
	return (NULL);
}

t_env		*my_unsetenv(char *var,char *val,t_env **l)
{
	char *str;

	var = ft_strjoin(var,"=");
	str = ft_strjoin(var,val);

	my_find_list_del(l, str);
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
	if(!setenv_err(var))
		if (!modif_env(&l,val,var))
		{
			var = ft_strjoin(var,"=");
			str = ft_strjoin(var,val);
			l = list_check_add(str,l);
		}
	return l;
}

int   modif_env(t_env **list,char *var, void *data_ref)
{
	char	*str;
	t_env	 *begin;
	begin = *list;
	unsigned int i;

	i = 0;
	while (begin && ft_memcmp(begin->content, data_ref,
				ft_strlen(data_ref)) != 0)
		begin = begin->next;
	i = ft_strlen(data_ref);
	if (begin && ((unsigned char*)begin->content)[i] == '=')
	{
		data_ref = ft_strjoin(data_ref,"=");
		str = ft_strjoin(data_ref,var);
		//free((unsigned char*)begin->content);
		begin->content = str;
		return 1;
	}
	return 0;
}
