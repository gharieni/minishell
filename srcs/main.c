#include "minishell.h"

void add_path(char **str,char **bin,char *argv)
{
	int i = -1;
	char *old_bin;

	while(bin && bin[++i])
	{
		old_bin = *(bin + i);
		bin[i] = ft_strjoin(bin[i],"/");
		ft_strdel(&old_bin);
//	if(*str)
		ft_strdel(str);
		*str = ft_strjoin(bin[i],argv);
		if (access(*str,R_OK) == 0)
		{
//			ft_freestrarr(bin);
			return;
		}
	}
//		printf("check me ligne 24 in the main \n");
	ft_strdel(str);
	*str = ft_strdup(argv);
}

static int		run_cmd(char *path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	//	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, args, env);
	else if (pid < 0)
	{
		free(path);
		ft_putendl("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	if (path)
		free(path);
	return (1);
}

static int	 exec_command(char *command,char **newargv,char **env)
{
	struct stat	f;

	if (lstat(command, &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			return (0);
		}
		else if (f.st_mode & S_IXUSR)
		return (run_cmd(ft_strdup(command), newargv,env));
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command);
	return (0);
}

int my_work(char **env,t_env **list,char *str)
{
	char **bin;
	char *path;
	char **newargv;
	int status =  0;

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
	else if(ft_strcmp(newargv[0],"echo") == 0)
	{
		check_echo(newargv,*list);
			return(free_without_fork(newargv,str));
	}
	else if(ft_strcmp(newargv[0],"env") == 0)
	{
		print_list(*list);
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
	else if(*newargv[0] == '.' && newargv[0][1] == '/' && access(str,R_OK))
		ft_putstr("file >>>>>>>>>>>>>>> \n");
	//	ft_fileserr(path);
	else if(*newargv[0] == '.' && !newargv[0][1])
		ft_putstr(".: not enough arguments\n");
	if (ft_noaccess(str) == 1)
		return(free_without_fork(newargv,str));
	env = my_exceve(str,*list);
	path = my_env(env);
	bin = ft_strsplit(path,':');
	str = del_tab(str);
	add_path(&str,bin,newargv[0]);
	if(bin && *bin)
		ft_freestrarr(bin);
	exec_command(str,newargv,env);
	//	if (access(str,X_OK) == -1 && *newargv[0] != '.')
	//	{
	//free_without_fork(newargv,str);
	//	return (0);
	//	}
	ft_freestrarr(newargv);
	ft_strdel(&str);
	ft_freestrarr(env);
	return(status);
}

int main(int ac , char **av, char **env)
{
	t_env	*list;
	char	*str;

	list = my_params_in_list(env);
	str = NULL;
	while (19 || ac || av)
	{
		ft_putstr(GRN);
		ft_putstr("•••••••  gmelek> ");
		ft_putstr(RESET);
		//		signal(SIGINT,signal_handler);
		get_next_line(0,&str);
		if(str && !ft_strlen(str))
			ft_strdel(&str);
		str = del_tab(str);
		
		while(str && ft_strcmp(str,"exit") == 0)
		{
			ft_strdel(&str);
			free_list(&list);
			exit (0);
		}
//	printf(">>>>>>>>>>>>>>>>>>%st\n",str);
		if(str)
			my_work(NULL,&list,str);
	}
	return (0);
}
