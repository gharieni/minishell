#include "minishell.h"

char *my_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if(ft_strncmp(env[i],"PATH=",5) == 0)
			return ((char*)env[i] + 5);
	return (NULL);
}

char *add_path(char **bin,char *argv)
{
	char *str;
	int i = -1;
	char *old_bin;
	while(bin[++i])
	{
		old_bin = *(bin + i);
		bin[i] = ft_strjoin(bin[i],"/");
		free(old_bin);
		str = ft_strjoin(bin[i],argv);
		if (access(str,R_OK) == 0)
			return(str);
		free(str);
	}

	return NULL;
}

void cd_dir(char **newargv)
{
	int i = 0;
	while(newargv[++i])
		if(newargv[i][0] != '-')
		{
			chdir(newargv[i]);
			return ;
		}
}

int my_work(char **env,t_list **list)
{
	char **bin;
	char *path;
	char **newargv;
	char *str;


	ft_putstr("•••••••  gmelek> ");
	path = my_env(env);
	bin = ft_strsplit(path,':');
	get_next_line(0,&str);
	newargv = strsplit(str);
	free(str);
	str = add_path(bin,newargv[0]);
	while(*bin)
	{
		*bin = NULL;
	free(*bin);
	bin ++;
	}
	if(ft_strcmp(newargv[0],"cd") == 0)
		cd_dir(newargv);
	else if(ft_strcmp(newargv[0],"exit") == 0)
		return(1);
	else if(ft_strcmp(newargv[0],"env") == 0)
	{
		print_list(*list);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"setenv") == 0)
	{
		*list = my_setenv(newargv[1],newargv[2],*list);
		return 0;
	}
	else if(ft_strcmp(newargv[0],"unsetenv") == 0)
	{
		my_unsetenv(newargv[1],newargv[2],*list);
		return 0;
	}
	return execve(str, newargv, env);
}

int main(int ac , char **av, char **env)
{
	int status;
	int options = 0;
	struct rusage usage;
	t_list *list;
	int t;
	pid_t pid;

	pid = (pid_t)NULL;
	list = my_params_in_list(env);
	while (42 || ac || av[0])
	{
		pid = fork();
		if (pid == 0)
		{		
		t = my_work(env,&list);
		if(t) exit(t == 1);
		}
		wait4(pid, &status, options, &usage);
		printf("∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫  status =  %d   \n",status);
		if(status == 256)
			exit(0);
	}
	return (0);
}
