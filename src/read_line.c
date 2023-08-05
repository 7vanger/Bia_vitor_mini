/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:05:43 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:05:58 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getchar(int fd)
{
	char	buf[BUFSIZ];
	char	*str;
	int		i;

	str = buf;
	i = 0;
	if (i == 0)
	{
		i = read(fd, buf, 1);
		str = buf;
	}
	if (--i >= 0)
		return (*str++);
	return (0);
}

static int	check_buffer(int buf_siz, char **buf, int str_siz)
{
	if (!buf_siz)
		return (0);
	buf_siz += buf_siz;
	buf = ft_realloc(buf, buf_siz);
	str_siz = buf_siz;
	return (str_siz);
}

static int	check_end(int fd, int buf_siz, char **buf)
{
	int	i;

	i = ft_getchar(fd);
	if (i == EOF)
	{
		if (buf_siz)
			free(buf);
		return ('\0');
	}
	return (i);
}

static char	*check_delim(int num, int i, char *buf, char *delim)
{
	char	*str;

	if (num == 2)
	{
		i = ft_stristr(buf, delim, ft_strlen(buf));
		if (i != 0)
		{
			str = ft_substr(buf, 0, i);
			return (str);
		}
		return (buf);
	}
	return (buf);
}

char	*ft_readline(int fd, int num, char *delim)
{
	char	*buf;
	int		i;
	int		buf_siz;
	int		str_siz;

	i = 0;
	buf_siz = 64;
	buf = ft_calloc(1, buf_siz);
	str_siz = buf_siz;
	while (1)
	{
		if (i == str_siz -1)
		{
			str_siz = check_buffer(buf_siz, &buf, str_siz);
			if (str_siz == 0)
			break ;
		}
		buf[i] = check_end(fd, buf_siz, &buf);
		if (buf[i] == '\n' || buf[i] == '\0')
			break ;
		i++;
	}
	buf[i] = '\0';
	buf = check_delim(num, i, buf, delim);
	return (buf);
}
