#include "minishell.h"

void    ft_comnotfound(char *bin)
{
        ft_putstr_fd("minishell: command not found: ", 2);
        ft_putendl_fd(bin, 2);
}

int	ft_fileserr(char *path)
{
	struct stat     *info;

	if (!(info = (struct stat *)malloc(sizeof(*info))))
		return (0);
	if (ft_strchr(path, '/') != NULL)
	{
		if (lstat(path, info) == -1)
			ft_putstr_fd("minishell: no such file or directory: ", 2);
		else
			ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(path, 2);
		free(info);
		return (1);
	}
	free(info);
	return (0);
}

int	ft_noaccess(char *path)
{
	struct stat	*info;
	if (!(info = (struct stat *)malloc(sizeof(*info))))
		return (0);
	if (lstat(path, info) != -1 && access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		if (ft_strrchr(path, '/'))
			ft_putendl_fd(ft_strrchr(path, '/') + 1, 2);
		else
			ft_putendl_fd(path, 2);
		free(info);
		return (1);
	}
	free(info);
	return (0);
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
