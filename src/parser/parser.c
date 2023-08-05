/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:08:42 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 18:56:03 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_token(t_token *token)
{
	int	i;

	i = 0;
	if (ft_strncmp(token->input, "<<", 2) == 0)
		token->id.in = here_doc(i, token);
	if (ft_strncmp(token->input, "<", 1) == 0)
		token->err = input_token(i, token);
	if (ft_strncmp(token->input, ">>", 2) == 0)
		token->err = output_token(i, token, 1);
	else if (ft_strncmp(token->input, ">", 1) == 0)
		token->err = output_token(i, token, 0);
	else
		token->input++;
}

void	if_opt(t_token *token)
{
	token->id.tmp = token->id.print;
	if (token->id.tmp == NULL && ft_strncmp(token->id.built, "cd", 2) == 0)
		token->id.tmp = "home";
	if (ft_strcmp(token->id.built, "cd") == 0)
	{
		if (ft_strncmp(token->id.tmp, "home", 4) == 0)
			home_path(token);
		else if (ft_strncmp(token->id.tmp, "/", 1) != 0)
			any_path(token);
		if (ft_strncmp(token->id.tmp, ".", 1) == 0)
			token->id.tmp++;
		if (ft_strncmp(token->id.tmp, "/", 1) == 0)
			direct_path(token);
	}
}

void	if_printf(int i, t_token *token)
{
	int	j;

	j = 1;
	while (ft_strncmp(token->id.built, "echo", 4) == 0 
			&& ft_strncmp(token->input, "-n", 2) == 0)
	{
		while (token->input[j + 1] != '\0' && token->input[j + 1] == 'n')
			j++;
		if (token->input[j + 1] != ' ' && token->input[j + 1] != '\0')
			break ;
		free(token->id.opt);
		token->id.opt = ft_strdup("-n");
		token->input = clear_word(count_until_char(token->input, i), 
				token->input);
		token->input = cut_space(token->input);
	}
	if (!token->id.print)
	{
		while (token->input && token_limit(token->input[0]) == 0)
		{
			if (token->input[0] == 34 || token->input[0] == 39)
				handle_quote(token, i);
			else
				process_Input_Token(token, i);
		}
	}
}

void	if_builtin(int i, t_token *token)
{
	char	*str;

	token->input = cut_space(token->input);
	i = delimeter_token(i, token->input);
	str = ft_substr(token->input, 0, i);
	if (ft_strncmp(str, "ECHO", 5) == 0)
		str = ft_ulstr(str);
	token->id.built = ft_strdup(str);
	free(str);
	token->input = clear_word(i, token->input);
	token->input = cut_space(token->input);
}

void	parser(t_token *token)
{
	int	i;

	i = 0;
	if_builtin(i, token);
	if_printf(i, token);
	if_opt(token);
	while (token->input[0] != '\0' && token->input[0] != '|')
		if_token(token);
	if (token->err > 0)
		free_buff(token);
}
