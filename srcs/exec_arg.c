#include "minishell.h"

static int free_without_fork(char **newargv, char *str)
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
int my_command(char *str, char **newargv, t_env **list)
{
	int t;

	t = 0;
	if(!newargv[0])
		return (0);
	ft_strcmp(newargv[0], "echo") == 0 ? check_echo(newargv,*list) : t++;
	ft_strcmp(newargv[0], "cd") == 0 ? cd_dir(newargv,*list) : t++;
	ft_strcmp(newargv[0], "env") == 0 ? print_list(*list) : t++;
	ft_strcmp(newargv[0], "unsetenv") == 0 ?
		((*list = my_unsetenv(newargv[1],newargv[2],list)) && 1)  : t++;
if (ft_strcmp(newargv[0],"setenv") == 0 || (++t && 0))
	{
		if(!newargv[1])
			print_list(*list);
		else if(newargv[3])
			ft_putendl_fd("setenv: Too many arguments.", 2);
		else
			*list = my_setenv(newargv[1],newargv[2],*list);
	}
	if (t < 5 || ft_noaccess(str) == 1)
		return(free_without_fork(newargv,str));
//	else if(*newargv[0] == '.' && newargv[0][1] == '/' && access(str,R_OK))
//		ft_putstr("file >>>>>>>>>>>>>>> \n"); a.out chmod 000
	else if(*newargv[0] == '.' && !newargv[0][1])
		ft_putstr(".: not enough arguments\n");
	return 1;
}
