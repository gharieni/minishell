#include "minishell.h"

static char	*trim_before(char *str)
{
	if (str)
	{
		while (*str == '\t' || *str == ' ')
			str++;
	}
	return (str);
}

static int	trim_end(char *str)
{
	int	id_end;

	id_end = ft_strlen(str);
	id_end--;
	if (str)
	{
		while (str[id_end] == '\t' || str[id_end] == ' ')
			id_end--;
	}
	return (id_end + 1);
}

char		*trim_trailing_whitespaces(char *str)
{
	char	*ptr;
	char	*trimmed;
	int		len_trimmed;
	int		i;

	if (!str)
		return (NULL);
	str = trim_before(str);
	len_trimmed = trim_end(str);
	if ((trimmed = (char *)malloc(sizeof(char) * (len_trimmed + 1))) == NULL)
		return (NULL);
	ptr = trimmed;
	i = 0;
	while (i < len_trimmed)
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
			*trimmed++ = str[i];
		else if ((i - 1 >= 0) && (!(str[i - 1] == ' ' || str[i - 1] == '\t')))
			(str[i] == '\t') ? (*trimmed++ = ' ') : (*trimmed++ = str[i]);
		i++;
	}
	*trimmed = '\0';
	return (ptr);
}
