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

int	builtins(t_token *token, char **envp, t_env *l_env)
{
	int		i;

	i = token->err;
	if (token->err > 0)
		return (ft_msg(i));
	else if (ft_strncmp (token->id.built, "echo", 5) == 0)
		i = execute_echo(token->id);
	else if (ft_strncmp(token->id.built, "cd", 3) == 0)
		i = execute_cd(token->id, l_env);
	else if (ft_strncmp(token->id.built, "pwd", 4) == 0)
		i = execute_pwd(token, l_env);
	else if (ft_strncmp(token->id.built, "export", 7) == 0)
		i = execute_export(token->id.print, l_env);
	else if (ft_strncmp(token->id.built, "unset", 6) == 0)
		i = execute_unset(token->id.print, l_env);
	else if (ft_strncmp(token->id.built, "env", 4) == 0)
		i = execute_env(l_env);
	else if (ft_strncmp(token->id.built, "exit", 5) == 0)
		return (execute_exit(token, token->id.print, l_env));
	else
		i = execute_path(token, envp, l_env);
	if (token->err == 0)
		free_buff(token);
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

void	if_builtin(int i, t_token *token)
{
	char	*str;

	token->input = cut_space(token->input);
	i = delimeter_token(i, token->input);
	printf("E: %s (%d)\n", token->input, i);//TESTE
	str = ft_substr(token->input, 0, i);
	if (ft_strncmp(str, "ECHO", 5) == 0)
		str = ft_ulstr(str);
	token->id.built = ft_strdup(str);
	free(str);
	token->input = clear_word(i, token->input);
	token->input = cut_space(token->input);
}
