#include"minishell.h"

void cd_dir(char **newargv,t_env *l)
{
	int i = 0;
	char *pwd;
	t_env *list;
	int k;

	k = -1;
	list = l;
	if(!newargv[1])
	{
		newargv[1] = ft_strdup("/Users/user");
		newargv[2] = NULL;
	}
	if(!ft_strcmp(newargv[1], "-"))
	{
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
	}
	while(newargv[++i] && (newargv[i][0] != '-'))
	{
		if (ft_cd_checkerrors(newargv[i]))
			return ;
		//	printf("test\n");
		pwd = getcwd(NULL, 0);
		modif_env(&l,pwd,"OLDPWD");
		chdir(newargv[i]);
		ft_strdel(&pwd);
		pwd = getcwd(NULL, 0);
		modif_env(&l,pwd,"PWD");
		ft_strdel(&pwd);
		//	return ;
	}
}

int	check_echo(char **argenv, t_env *l)
{
	t_env *list;
	int i;
	int k;

	list = l;
	k = 0;
	i = 1;
	if (argenv[1] == NULL)
		return 0;
	if(!ft_strcmp(argenv[1],"-n"))
		i = 2;
	while(argenv[i])
		if (argenv[i][0] == '$')
		{
			list = l;
			k = 0;
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
	if(ft_strcmp(argenv[1],"-n") != 0)
		ft_putendl("");
	return 0;
}

void    ft_cd_puterr(char *path, char *message)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
}

int  ft_cd_checkerrors(char *path)
{
	struct stat		*st;

	if (!(st = (struct stat *)malloc(sizeof(*st))))
		return (1);
	if (stat(path, st) == -1)
	{
		ft_cd_puterr(path, "No such file or directory");
		free(st);
		return (1);
	}
	else if (S_ISDIR(st->st_mode) != 1)
	{
		ft_cd_puterr(path, "Not a directory");
		free(st);
		return (1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_cd_puterr(path, "Permission denied");
		free(st);
		return (1);
	}
	free(st);
	return (0);
}
