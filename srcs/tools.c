/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:55:31 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/17 10:10:51 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char **my_exceve(char *str, t_env *list)
{
	char **env;
	int i = 0;

	env = NULL;
	if(str || 1)
		env = malloc((list_count(list) + 1) * sizeof (char*));
	while(list)
	{
	env[i] = ft_strdup(list->content);
	i++;
	list = list->next;
	}
	env[i] = NULL;
return env;
}

static const char		*ft_str_find_next(const char *str, int skip)
{
	if (skip)
		while (*str != '\0' && *str == ' ')
			str++;
	else
		while (*str != '\0' && *str != ' ')
			str++;
	return (str);
}

static int				ft_str_count_splits(const char *str)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		str = ft_str_find_next(str, 1);
		if (*str != '\0')
		{
			i++;
			str = ft_str_find_next(str, 0);
		}
	}
	return (i);
}

static char				**ft_tabledel(char **ret, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(ret[i]);
	free(ret);
	return (NULL);
}

char *del_tab(char *str)
{
	int i;

	i = -1;

	while(str[++i])
		if(str[i] == '\t')
			str[i] = ' ';
		return str;
}

char					**strsplit(char const *str)
{
	char		**ret;
	int			i;
	const char	*next;

	if (str == NULL)
		return (NULL);
	ret = malloc(sizeof(char*) * (ft_str_count_splits(str) + 2));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		str = ft_str_find_next(str, 1);
		if (*str != '\0')
		{
			next = ft_str_find_next(str, 0);
			ret[i] = ft_strsub(str, 0, next - str);
			if (ret[i] == NULL)
				return (ft_tabledel(ret, i));
			i++;
			str = next;
		}
	}
	ret[i] = NULL;
	return (ret);
}
