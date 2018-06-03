/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 14:39:10 by gmelek            #+#    #+#             */
/*   Updated: 2017/01/17 20:00:38 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include"get_next_line.h"

static int gnl_check_stock(char **stock, char **line)
{
	char *tmp;

	if ((tmp = ft_strchr(*stock, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}
	return (0);
}

static int gnl_check_read(char *buffer, char **stock, char **line)
{
	char *tmp;

	if((tmp = ft_strchr(buffer, '\n')))
	{
		*tmp = '\0';
		*line = ft_strjoin(*stock, buffer);
		free(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		free(buffer);
		return (1);
	}
	return (0);
}

int get_next_line(const int fd, char **line)
{
	char *buffer;
	static char *stock = NULL;
	int ret;

	buffer = ft_strnew(BUFF_SIZE);
	if(fd < 0 || !line || read(fd, buffer, 0) < 0)
		return (-1);
	if (stock)
		if (gnl_check_stock(&stock, line))
			return (1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (gnl_check_read(buffer, &stock, line))
			return (1);
		stock = ft_strjoin(stock, buffer);
	}
	free(buffer);
	buffer = NULL;
	if (ret == -1)
		return (-1);
	if (stock == NULL)
		return (0);
	*line = ft_strdup(stock);
	free(stock);
	stock = NULL;
	return ((ft_strlen(*line) > 0));
}

/*
int     main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	line = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
	 ret = get_next_line(fd, &line);
		ft_putstr(line);
	ft_putnbr(ret);
		
		close(fd);
	}
	return(0);
}*/
