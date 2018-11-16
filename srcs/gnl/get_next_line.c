/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:17:07 by ghamelek          #+#    #+#             */
/*   Updated: 2018/11/09 13:04:50 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_check_stock(char **stock, char **line)
{
	char	*tmp;
	char	*tmp2;
	char	*s;

	if ((tmp = ft_strchr(*stock, 0x0a)))
	{
		*tmp = '\0';
		s = malloc(ft_strlen(*stock) + 1);
		*line = ft_strcpy(s, *stock);
		tmp2 = *stock;
		s = NULL;
		s = malloc(ft_strlen(tmp + 1) + 1);
		*stock = ft_strcpy(s, tmp + 1);
		ft_strdel(&(tmp2));
	//	printf("%p    ||    %p \n",s,(tmp + 1));
		return (1);
	}
	return (0);
}

static int	gnl_check_read(char *buffer, char **stock, char **line)
{
	char *tmp;
	char *s;

	s = NULL;
	if ((tmp = ft_strchr(buffer, '\n')))
	{
		*tmp = '\0';
		*line = ft_strjoin(*stock, buffer);
		ft_strdel(stock);
		s = malloc(ft_strlen(tmp + 1) + 1);
		*stock = ft_strcpy(s, tmp + 1);
		ft_strdel(&buffer);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char		*buf;
	static char	*stock[5000];
	int			ret;
	char		*s;

	buf = NULL;
	if (fd > 5000 || fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (*(stock + fd) && (gnl_check_stock((stock + fd), line)))
		return (1);
	if(!(buf = malloc(BUFF_SIZE + 1)))
	{
		printf("error !!!");
		return (-1);
	}	
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (((buf[ret] = '\0') + 1) && gnl_check_read(buf, (stock + fd), line))
			return (1);
			s = *(stock + fd);
		*(stock + fd) = ft_strjoin(*(stock + fd), buf);
		ft_strdel(&s);
	}
	ft_strdel(&buf);
	if (*(stock + fd) == NULL)
		return (0);
	*line = ft_strdup(*(stock + fd));
	ft_strdel((stock + fd));
//	*(stock + fd) = NULL;
	return ((ft_strlen(*line) > 0));
}
