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
	printf("ııııııııı   str = %p >>>>> bin = %p\n",*str,bin[i]);
		*str = ft_strjoin(bin[i],argv);
	printf("ııııııııı   str = %p >>>>> bin = %p\n",*str,bin[i]);
		if ((k = access(*str,R_OK)) == 0)
		{
printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	ft_freestrarr(bin);
	return;
		}
	}
	
//	ft_freestrarr(bin);
	ft_strdel(str);
	*str = ft_strdup(argv);
}

int my_work(char **env,t_env **list,char *str)
{
	char **bin;
	char *path;
	char **newargv;
	int status;
	pid_t pid;
	
	newargv = NULL;
	env = my_exceve(str,*list);
	path = my_env(env);
	bin = ft_strsplit(path,':');
	newargv = strsplit(str);
//				ft_strdel(&str);
//	printf("<<<<<<<<<<<<<<<<<  %p \n",str);
	add_path(&str,bin,newargv[0]);
	printf("ııııııııı   str = %p >>>>> bin = %p\n",str,bin);
	//ft_freestrarr(bin);
	pid = fork();
//			signal(SIGINT,handler);
	if(pid == 0)
	{
		execution(str, env, newargv, list);
	}
	wait(&status);
	ft_freestrarr(newargv);
		ft_strdel(&str);
	ft_freestrarr(env);
	if(status == 65280)
		exit (-1);
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
		ret = my_work(NULL,&list,str);
			printf("hooooooooooooooooooooolllllllllllllaaaaaaaaaaa  %s \n",str);
	//	ft_strdel(&str);
	}
	return (0);
}
