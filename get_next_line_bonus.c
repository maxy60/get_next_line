/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:56:21 by msainton          #+#    #+#             */
/*   Updated: 2021/07/15 12:40:31 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check(char *str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
	{
		if (str[a] == '\n' || str[a] == '\0')
			return (1);
		a++;
	}
	return (0);
}

static char	*ft_error(char *dest)
{
	if (dest)
	{
		free(dest);
		dest = 0;
	}
	return (NULL);
}

static char	*retgnl(char **dest, char *line, int ret, int fd)
{
	if (ret == 0)
	{
		free(dest[fd]);
		dest[fd] = NULL;
		if (line[0] == '\0')
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*dest[1024];
	char		*line;
	int			ret;

	ret = 1;
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, NULL, 0) != 0)
		return (ft_error(dest[fd]));
	if (!dest[fd])
	{
		dest[fd] = (char *)malloc(sizeof(char) * 1);
		dest[fd][0] = '\0';
	}
	while (ret != 0 && check(dest[fd]) == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (ft_error(dest[fd]));
		buf[ret] = '\0';
		dest[fd] = ft_strjoin(dest[fd], buf);
	}
	line = stock_line(dest[fd], ret);
	dest[fd] = stock_rest(dest[fd]);
	return (retgnl(dest, line, ret, fd));
}
