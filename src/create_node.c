/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:04:14 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:04:28 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token(t_token *token)
{
	token->id.out = STDOUT_FILENO;
	token->id.print = NULL;
	token->id.in = STDIN_FILENO;
	token->id.opt = ft_calloc(1, sizeof(char));
	token->id.path = ft_calloc(1, sizeof(char));
}

t_token	*go_node(t_token *token)
{
	while (token->input[0] != '\0')
	{
		set_token(token);
		if (pipe(token->fd) == -1)
			return (NULL);
		parser(token);
		if (token->input[0] == '|')
		{
			token->input++;
			if (token->input[0] == '\0')
				token->err = 1;
		}
		if (token->input[0] != '\0' && token->err == 0)
		{
			token->next = ft_calloc(1, sizeof(t_token));
			token->next->input = token->input;
			token->next->prev = token;
			token = token->next;
			token->index = token->prev->index + 1;
		}
	}
	return (token);
}

t_token	*create_node(char *str, t_token *token)
{
	t_token	*rec;
	char	*obj;
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	tmp = ft_strdup(str);
	obj = expand(tmp, i);
	token = ft_calloc(1, sizeof(t_token));
	token->index = i;
	token->input = obj;
	token->err = 0;
	rec = token;
	while (token->input[0] != '\0')
		token = go_node(token);
	g_env.pipenum = token->index;
	free(obj);
	return (rec);
}

