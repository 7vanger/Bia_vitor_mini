/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:09:34 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:09:47 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	any_path(t_token *token, t_env e_env)
{
	token->id.path = paste_char(token->id.path, e_env.pwd);
	//printf("any_id.path: %s\n", token->id.path);
	if (token->id.path[ft_strlen(token->id.path) - 1] != '/')
		token->id.path = paste_char(token->id.path, "/");
	//printf("any_id.path: %s\n e o tmp: %s\n", token->id.path, token->id.tmp);
	while (token->id.tmp[0] == '/' || ft_isalnum(token->id.tmp[0]) == 1 ||
			ft_strncmp(token->id.tmp, "..", 2) == 0)
	{
		if (token->id.tmp[0] == '/' || ft_isalnum(token->id.tmp[0]) == 1)
			add_section(token);
		else if (ft_strncmp(token->id.tmp, "..", 2) == 0)
			remove_section(token);
		if (ft_strncmp(token->id.tmp, "./", 2) == 0)
			token->id.tmp += 2;
	}
}

void	direct_path(t_token *token)
{
	while (token->id.tmp[0] == '/' || ft_isalnum(token->id.tmp[0] == 1) ||
			ft_strncmp(token->id.tmp, "..", 2) == 0)
	{
		if (token->id.tmp[0] == '/' || ft_isalnum(token->id.tmp[0]) == 1)
		    add_section(token);
		else if (ft_strncmp(token->id.tmp, "..", 2) == 0)
			remove_section(token);
		if (ft_strncmp(token->id.tmp, "./", 2) == 0)
			token->id.tmp += 2;
	}
}

void	home_path(t_token *token, t_env e_env)
{
	free(token->id.path);
	token->id.path = ft_strdup(e_env.home);
	return ;
}
