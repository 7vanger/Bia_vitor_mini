/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:09:11 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:09:25 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	scan_for_word(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == 32)
		i++;
	if (input[i] == '|')
		return (0);
	if (input[i] == '<')
		return (0);
	if (input[i] == '>')
		return (0);
	if (ft_isprint(input[i]) == 1 && input[i] != 32)
		return (1);
	return (2);
}

void	process_Input_Token(t_token *token, int i)
{
	char *sub;

	i = delimeter_token(i, token->input);
	if (i > 0)
	{
		sub = ft_substr(token->input, 0, i);
		if (token->id.print == NULL)
			token->id.print = ft_strdup(sub);
		else
			token->id.print = paste_char(token->id.print, sub);
		free(sub);
	}
	else if (token->input && i == 0 && token->input[i] == ' ')
	{
		while (*token->input == ' ' && !ft_isalnum(token->input[1]))
			token->input++;
		if (scan_for_word(token->input) && token->id.print != NULL)
			token->id.print = paste_char(token->id.print, " ");
		token->input = cut_space(token->input);
	}
	else
		token->id.print = ft_calloc(1, sizeof(char));
	while (*token->input && i--)
		token->input++;
}

int	token_limit(char c)
{
	if (!c)
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '|')
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

int	delimeter_token(int i, char *str)
{
	if (!str)
		return (0);
	i = cut_before_first_char(str, 34);
	if (i > cut_before_first_char(str, ' '))
		i = cut_before_first_char(str, ' ');
	if (i > cut_before_first_char(str, 39))
		i = cut_before_first_char(str, 39);
	if (i > cut_before_first_char(str, '|'))
		i = cut_before_first_char(str, '|');
	if (i > cut_before_first_char(str, '<'))
		i = cut_before_first_char(str, '<');
	if (i > cut_before_first_char(str, '>'))
		i = cut_before_first_char(str, '>');
	return (i);
}
