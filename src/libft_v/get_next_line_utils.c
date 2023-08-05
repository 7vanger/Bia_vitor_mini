/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:33:14 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:33:26 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
	{
		free(s);
		return (0);
	}
	while (s[i] != 0)
	{
		if (s[i] == (unsigned char)c)
			return (s + i);
		i++;
	}
	if ((unsigned char)c == 0)
		return (s + i);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != 0)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_to_name(char *name, char *s1, char *s2)
{	
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s1[j])
	{
		name[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		name[i] = s2[j];
		i++;
		j++;
	}
	name[i] = 0;
	return (name);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*name;

	if (!s1)
		return (0);
	name = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!name)
		return (0);
	name = ft_to_name(name, s1, s2);
	free(s1);
	return (name);
}
