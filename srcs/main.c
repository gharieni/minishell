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
	return argv;
}

int my_work(char **env,t_env **list,char *str)
{
	char **bin;
	char *path;
	char **newargv;
	int status;

	newargv = NULL;
	env = my_exceve(str,newargv,*list);
	path = my_env(env);
	bin = ft_strsplit(path,':');
	str = del_tab(str);
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
	pid_t pid;
	int ret = 0;
	pid = fork();
		signal(SIGINT,handler);
	if(pid == 0)
		ret = execution(str, env, newargv, list);
	wait(&status);
	if(status == 65280)
	exit (-1);
		return(ret);
}

int main(int ac , char **av, char **env)
{
	t_env *list;
	char *str;
	int ret;

	list = my_params_in_list(env);
	str = NULL;
	while (42 || ac || av)
	{
		
		ft_putstr("•••••••  gmelek> ");
		signal(SIGINT,signal_handler);
		get_next_line(0,&str);
		ret = my_work(NULL,&list,str);
	}
	return (0);
}
