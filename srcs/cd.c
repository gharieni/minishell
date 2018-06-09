#include"minishell.h"

void cd_dir(char **newargv,t_env *l)
{
	int i = 0;
	char *pwd;

	if(!newargv[1])
		newargv[1] = "/Users/user";
	if(!ft_strcmp(newargv[1], "-"))
		printf("hooooooooooooooooopa\n");
		//<< normalement aaprend old pwd
		//attendre a verifier les variable 
		//	return ;
	while(newargv[++i])
		if(newargv[i][0] != '-')
		{
			if (ft_cd_checkerrors(newargv[i]))
				return ;
			pwd = getcwd(NULL, 0);
			modif_env(&l,pwd,"OLDPWD");
			chdir(newargv[i]);
			pwd = getcwd(NULL, 0);
			modif_env(&l,pwd,"PWD");
			ft_strdel(&pwd);
			return ;
		}
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
