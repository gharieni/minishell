#include "minishell.h"

int free_without_fork(char **newargv, char *str)
{
	ft_freestrarr(newargv);
	ft_strdel(&str);
	return (0);
}
void execution(char *str,char **env, char **newargv,t_env **list)
{
		//signal(SIGINT,handler);
	if(list || 1)
		execve(str, newargv, env);
}

