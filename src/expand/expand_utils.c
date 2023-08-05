/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:08:07 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:08:22 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_content(char *content, char *add, int pos, char *var)
{
	char	*mod;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	mod = ft_calloc(1, (ft_strlen(content)) + ft_strlen(add));
	while (i != pos)
	{
		mod[i] = content[i];
		i++;
	}
	k = i;
	while (add[j])
		mod[i++] = add[j++];
	j = ft_strlen(var) + k;
	while (k < j)
		k++;
	while (content[k])
		mod[i++] = content[k++];
	mod[i] = '\0';
	free (content);
	return (mod);
}

int	skip_single_quote(char *str, int i)
{
	i++;
	while (str[i] != 39 && str[i] != '\0')
		i++;
	if (str[i] == 39)
		i++;
	return (i);
}
