#include "minishell.h"

char *add_path(char **bin,char *argv)
{
	char *str;
	int i = -1;
	char *old_bin;
	int k;
	while(bin[++i])
	{
		old_bin = *(bin + i);
		bin[i] = ft_strjoin(bin[i],"/");
		free(old_bin);
		str = ft_strjoin(bin[i],argv);
		if ((k = access(str,R_OK)) == 0)
			return(str);
		free(str);
	}
	if(argv[0] != '.' && k == -1)
		ft_comnotfound(argv);
	return argv;
}

int my_work(char **env,t_env **list)
{
	char **bin;
	char *path;
	char **newargv;
	char *str;

str = NULL;
newargv = NULL;
	ft_putstr("•••••••  gmelek> ");
	env = my_exceve(str,newargv,*list);
	path = my_env(env);
	bin = ft_strsplit(path,':');
	get_next_line(0,&str);
	newargv = strsplit(str);
	free(str);
	str = add_path(bin,newargv[0]);

/**
 *  free bin    // leaks 
 *
	while(*bin)
	{
		*bin = NULL;
		free(*bin);
		bin ++;
	}
*/
	
	if(ft_strcmp(newargv[0],"cd") == 0)
	{
		cd_dir(newargv,*list);
		char *buff = NULL;
		buff = getcwd(buff,255);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"exit") == 0)
		return(1);
	else if(ft_strcmp(newargv[0],"env") == 0)
	{
		print_list(*list);
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
		my_unsetenv(newargv[1],newargv[2],*list);
		return 0;
	}
	if (ft_noaccess(str) == 1)
		return 1;
return execve(str, newargv, env);
}

int main(int ac , char **av, char **env)
{
	int status;
	int options = 0;
	struct rusage usage;
	t_env *list;
	int t;
	pid_t pid;

	pid = (pid_t)NULL;
	list = my_params_in_list(env);
	while (42 || ac || av[0])
	{
		pid = fork();
		if (pid == 0)
		{		
			t = my_work(NULL,&list);
			if(t) exit(t == 1);
		}
		wait4(pid, &status, options, &usage);
		if(status == 256)
			exit(0);
	}
	return (0);
}
