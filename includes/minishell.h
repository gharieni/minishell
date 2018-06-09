#ifndef MINISHEL_H
# define MINISHEL_H

#include "../srcs/gnl/get_next_line.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <signal.h>
#include <dirent.h>

typedef struct		s_env
{
	char			*content;
	char			*var;
	size_t			content_size;
	struct s_env	*next;
}					t_env;



void print_list(t_env *l);
char	**my_exceve(char *str, char **newargv, t_env *list);
int		list_count (const t_env *list);
void	ft_comnotfound(char *bin);
int		ft_fileserr(char *path);
int		ft_noaccess(char *path);
void	cd_dir(char **newargv,t_env *l);
int		ft_cd_checkerrors(char *path);
void	my_find_list_del(t_env **list, void *data_ref);
int		modif_env(t_env **list,char *var, void *data_ref);
char	*my_env(char **env);
t_env	*my_setenv(char *var,char *val,t_env *l);
t_env  *my_unsetenv(char *var,char *val,t_env *l);
t_env	*list_check_add(void* data, t_env* list);
t_env	*my_params_in_list(char **av);
char	**strsplit(char const *str);

#endif
