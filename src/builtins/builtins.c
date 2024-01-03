/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:58:14 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 14:58:58 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_token *token, char **envp)
{
	int		i;

	i = token->err;
	if (token->err > 0)
		return (ft_msg(i));
	else if (ft_strncmp (token->id.built, "echo", 5) == 0)
		i = execute_echo(token->id);
	else if (ft_strncmp(token->id.built, "cd", 3) == 0)
		i = execute_cd(token->id);
	else if (ft_strncmp(token->id.built, "pwd", 4) == 0)
		i = execute_pwd(token);
	else if (ft_strncmp(token->id.built, "export", 7) == 0)
		i = execute_export(token->id.print);
	else if (ft_strncmp(token->id.built, "unset", 6) == 0)
		i = execute_unset(token->id.print);
	else if (ft_strncmp(token->id.built, "env", 4) == 0)
		i = execute_env();
	else if (ft_strncmp(token->id.built, "exit", 5) == 0)
		return (execute_exit(token, token->id.print));
	else
		i = execute_path(token, envp);
	if (token->err == 0) {
		free_buff(token);
	}
	return (g_env.retval = ft_msg(i));
}

int	is_builtin(t_token *token)
{
	if (ft_strncmp(token->id.built, "echo", 5) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "cd", 3) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "export", 7) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "unset", 6) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "env", 4) == 0)
		return (0);
	if (ft_strncmp(token->id.built, "exit", 5) == 0)
		return (0);
	else
		return (1);
	return (1);
}
