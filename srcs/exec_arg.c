#include "minishell.h"



int execution(char *str,char **env, char **newargv,t_env **list)
{
	

//	signal(SIGINT,handler);
	if(!newargv[0])
		return 0;
	if(ft_strcmp(newargv[0],"cd") == 0)
	{
		cd_dir(newargv,*list);
		char *buff = NULL;
		buff = getcwd(buff,255);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"exit") == 0)
	{
		//ft_freestrarr(env);
		exit (-1);
	}
	else if(ft_strcmp(newargv[0],"env") == 0)
	{
		print_list(*list);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"echo") == 0)
	{
		if (check_echo(newargv,*list))
			return 0;
	}
	else if(ft_strcmp(newargv[0],"setenv") == 0)
	{
		if(!newargv[1])
			print_list(*list);
		if(newargv[3])
			ft_putendl_fd("setenv: Too many arguments.", 2);
		else
			*list = my_setenv(newargv[1],newargv[2],*list);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"unsetenv") == 0)
	{
		*list = my_unsetenv(newargv[1],newargv[2],list);
		return 0;
	}
	else if (access(str,R_OK) == -1 && *newargv[0] != '.')
	{
		ft_comnotfound(*newargv);
		return 0;
	}
	else if(*newargv[0] == '.' && newargv[0][1] == '/' && access(str,R_OK))
		printf("file >>>>>>>>>>>>>>> \n");
	else if(*newargv[0] == '.' && !newargv[0][1])
		printf("%s: not enough arguments\n",newargv[0]);
	
	if (ft_noaccess(str) == 1)
		return 0;
	return execve(str, newargv, env);

	return 0;
}
