#include"minishell.h"

static void cd_dir_suite(char **newargv,t_env *l)
{
	char *pwd;
	int i;

	i = 0;
	while(newargv[++i] && (newargv[i][0] != '-'))
	{
		if (ft_cd_checkerrors(newargv[i]))
			return ;
		pwd = getcwd(NULL, 0);
		modif_env(&l,pwd,"OLDPWD");
		chdir(newargv[i]);
		ft_strdel(&pwd);
		pwd = getcwd(NULL, 0);
		modif_env(&l,pwd,"PWD");
		ft_strdel(&pwd);
	}

}

void cd_dir(char **newargv,t_env *l)
{
	t_env *list;
	int k;

	k = -1;
	list = l;
	if(!newargv[1] && ((newargv[2] = NULL) || 1))
		newargv[1] = ft_strdup("/Users/user");
	if(!ft_strcmp(newargv[1], "-"))
		while (list)
		{
			if(!ft_strcmp("OLDPWD",list->var))
			{
				while(list->content[++k] != '=')
				{
					ft_strdel(&newargv[1]);
					newargv[1] = ft_strdup(list->content + 2 + ++k);
					newargv[2] = NULL;
				}
				break;
			}
			list = list->next;
		}
	cd_dir_suite(newargv,list);
}

static void	check_echo_suite(char **argenv, t_env *l,int i)
{
	t_env *list;
	int k;

	list = l;
	while(argenv[i])
		if ((argenv[i][0] == '$') && ((list = l) || 1) && ((k = 0) || 1))
		{
			while (list)
				if(!ft_strcmp(argenv[i] + 1,list->var))
				{
					while(list->content[++k] != '=');
					ft_putstr(list->content + ++k);
					list = NULL;
				}
				else
					list = list->next;
			if(argenv[++i])
				ft_putchar(' ');
		}
		else
		{
			ft_putstr(argenv[i]);
			if(argenv[++i])
				ft_putchar(' ');
		}
}

int	check_echo(char **argenv, t_env *l)
{
	int i;

	i = 1;
	if (argenv[1] == NULL)
		return 0;
	if(!ft_strcmp(argenv[1],"-n"))
		i = 2;
	check_echo_suite(argenv, l,i);
	if(ft_strcmp(argenv[1],"-n") != 0)
		ft_putendl("");
	return 0;
}

char *del_tab(char *str)
{
	int i;

	i = -1;

	while(str && str[++i])
		if(str[i] == '\t')
			str[i] = ' ';
		return str;
}
