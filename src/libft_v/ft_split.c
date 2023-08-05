/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:18:18 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 18:33:28 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(char *line, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == c)
			i++;
		if (line[i] != '\0')
			j++;
		while (line[i] && line[i] != c)
			i++;
	}
	return (j);
}

static char	*ft_strndup(char *line, size_t n)
{
	char	*str;

	str = malloc(sizeof(char) * (n + 1));
	if (!str)
	{
		free(str);
		return (0);
	}
	ft_memcpy(str, line, n);
	str[n] = '\0';
	return (str);
}

char	**ft_split(char *line, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	str = malloc(sizeof(char *) * (count_num(line, c) + 1));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (++i < count_num(line, c))
	{
		while (line[j] == c)
			j++;
		k = j;
		while (line[j] && line[j] != c)
			j++;
		str[i] = ft_strndup(line + k, j - k);
		if (!str[i])
			return (0);
	}
	str[i] = NULL;
	return (str);
}
