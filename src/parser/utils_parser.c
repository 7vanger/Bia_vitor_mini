/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:09:54 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 18:53:38 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*paste_char(char *str, char *new)
{
	size_t	str_len;
	size_t	new_len;
	char	*fusion;

	str_len = ft_strlen(str);
	new_len = ft_strlen(new);
	if (!str)
		return (ft_strdup(new));
	if (str_len == 1 && str[0] == '/' && new[0] == '/')
		new++;
	fusion = (char *)malloc((str_len + new_len + 1) * sizeof(char));
	if (!fusion)
		return (NULL);
	ft_memcpy(fusion, str, str_len);
	ft_memcpy(fusion + str_len, new, new_len);
	fusion[str_len + new_len] = '\0';
	free(str);
	return (fusion);
}

int	cut_until_char(char *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (ptr != NULL)
		return ((int)(ptr - str));
	else
		return (ft_strlen(str));
}

int	cut_before_first_char(char *input, char c)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	while (input[j])
	{
		if (input[j] == c)
		{
			while (input[i] != c && input[i] != '\0')
			{
				i++;
				len--;
			}
			return (i);
		}
		j++;
	}
	return (len);
}

void	handle_quote(t_token *token, int i)
{
	char	c;
	char	*tmp;	

	c = token->input[0];
	token->input++;
	i = cut_until_char(token->input, c);
	if (i == 0)
	{
		token->input++;
		return ;
	}
	if (i > 0)
	{
		tmp = ft_substr(token->input, 0, i);
		if (token->id.print == NULL)
			token->id.print = ft_strdup(tmp);
		else
			token->id.print = paste_char(token->id.print, tmp);
		free(tmp);
	}
	else
		token->id.print = ft_calloc(1, sizeof(char));
	while (i-- + 1)
		token->input++;
}
