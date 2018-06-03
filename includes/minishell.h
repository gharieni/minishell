#ifndef MINISHEL_H
# define MINISHEL_H

#include "../srcs/gnl/get_next_line.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
void    my_find_list_del(t_list **list, void *data_ref);
t_list	*my_setenv(char *var,char *val,t_list *l);
t_list  *my_unsetenv(char *var,char *val,t_list *l);
t_list	*list_check_add(void* data, t_list* list);
void	print_list(t_list *l);
t_list	*my_params_in_list(char **av);
char	**strsplit(char const *str);

#endif
