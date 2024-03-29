/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:10 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:06:24 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_space(char *token)
{
	while (*token <= 32 && *token != '\0')
		token++;
	return (token);
}

char	*clear_word( int i, char *input)
{
	while (i > 0 && *input != '\0')
	{
		input++;
		i--;
	}
	return (input);
}

int	count_until_char(char *input, int i)
{
	while (input[i] > 32)
		i++;
	return (i);
}

void	free_pointers_2(char **str, int i)
{
	int	j;

	i = 0;
	j = 0;
	while (str[j] != NULL)
		j++;
	while (i < j)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
