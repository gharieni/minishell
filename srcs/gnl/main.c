#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return 0;
	while(get_next_line(fd, &line) == 1)
	{
		ft_putstr(line);
		ft_putstr("\n");
		ft_strdel(&line);

	}
	ft_strdel(&line);
	close(fd);
//	while(1);
	return(0);
}

