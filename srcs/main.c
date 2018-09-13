#include "minishell.h"

void add_path(char **str,char **bin,char *argv)
{
	int i = -1;
	char *old_bin;
	int k;

	while(bin[++i])
	{
		old_bin = *(bin + i);
		bin[i] = ft_strjoin(bin[i],"/");
		ft_strdel(&old_bin);
		ft_strdel(str);
		*str = ft_strjoin(bin[i],argv);
		if ((k = access(*str,R_OK)) == 0)
		{
			ft_freestrarr(bin);
			return;
		}
	}

	//	ft_freestrarr(bin);
	//	printf("check me ligne 24 in the main \n");
	ft_strdel(str);
	*str = ft_strdup(argv);
}

int my_work(char **env,t_env **list,char *str)
{
	char **bin;
	char *path;
	char **newargv;
	int status =  0;
	pid_t pid;

	newargv = NULL;
	if(str)
		newargv = strsplit(str);
	
	if(!newargv[0])
		return (0);
	if(ft_strcmp(newargv[0],"cd") == 0)
	{
		cd_dir(newargv,*list);
			return(free_without_fork(newargv,str));
	}
	else if(ft_strcmp(newargv[0],"env") == 0)
	{
		print_list(*list);
			return(free_without_fork(newargv,str));
	}
	else if(ft_strcmp(newargv[0],"echo") == 0)
	{
		if (!check_echo(newargv,*list))
			return(free_without_fork(newargv,str));
	}
	else if(ft_strcmp(newargv[0],"setenv") == 0)
	{
		if(!newargv[1])
			print_list(*list);
		if(newargv[3])
			ft_putendl_fd("setenv: Too many arguments.", 2);
		else
			*list = my_setenv(newargv[1],newargv[2],*list);
		return(free_without_fork(newargv,str));
	}
	else if(ft_strcmp(newargv[0],"unsetenv") == 0)
	{
		*list = my_unsetenv(newargv[1],newargv[2],list);
		
		return(free_without_fork(newargv,str));
	}
//	else if (access(str,R_OK) == -1 && *newargv[0] != '.')
//	//{
//ft_putstr(">>>>>>>>>>>>>>>>>>>>");
//		ft_comnotfound(*newargv);
//			return(free_without_fork(newargv,str));
//	}
	else if(*newargv[0] == '.' && newargv[0][1] == '/' && access(str,R_OK))
		ft_putstr("file >>>>>>>>>>>>>>> \n");
	else if(*newargv[0] == '.' && !newargv[0][1])
		ft_putstr(".: not enough arguments\n");
	
	if (ft_noaccess(str) == 1)
			return(free_without_fork(newargv,str));


	
	
	
	
	
	
	
	
	
	
	env = my_exceve(str,*list);
	path = my_env(env);
	bin = ft_strsplit(path,':');
	str = del_tab(str);
	add_path(&str,bin,newargv[0]);

	pid = fork();
	//			signal(SIGINT,handler);
	if(pid == 0)
	{
		execution(str, env, newargv, list);
	}
	printf(">>>>>>>>>>>   %d \n",status);
	wait(&status);
	ft_freestrarr(newargv);
	ft_strdel(&str);
	ft_freestrarr(env);
	return(status);
}

int main(int ac , char **av, char **env)
{
	t_env	*list;
	char	*str;
	int		ret;

	list = my_params_in_list(env);
	str = NULL;
	while (42 || ac || av)
	{
		ft_putstr("•••••••  gmelek> ");
		//		signal(SIGINT,signal_handler);
		get_next_line(0,&str);
		while(1)
			if(ft_strcmp(str,"exit") == 0)
			{
				ft_strdel(&str);
				free_list(&list);
				return (0);
			}
			else
				break;
		ret = my_work(NULL,&list,str);
	}
	return (0);
}
