/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sous <ade-sous@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:11:26 by vlopes            #+#    #+#             */
/*   Updated: 2024/01/02 08:18:35 by ade-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_path(t_token *token, char **envp, t_env e_env)
{
	if (token->id.in == -1 || token->id.out == -1)
		return (2);
	if (token->id.built[0] == '\0')
		return (0);
	if (ft_strncmp(token->id.built, "/", 1) == 0)
	{
		if (access(token->id.built, F_OK) != 0)
			return (5);
		return (exec_parent(token, envp, e_env));
	}
	else
		return (get_path(&token->id, token, envp, e_env));
}

int	exec_parent(t_token *token, char **envp, t_env e_env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(token, NULL, envp, e_env);
	else if (child < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (child != 0 && token->index > 0)
	{
		close(token->prev->fd[0]);
		close(token->fd[1]);
	}
	if (child != 0)
		waitpid(0, &status, 0);
	if (token->id.in != STDIN_FILENO)
		close(token->id.in);
	if (token->id.out != STDOUT_FILENO)
		close(token->id.out);
	return (errno);
}

void	exec_child(t_token *token, char *path, char **envp, t_env e_env)
{
	char	**tmp;

	if (!path)
		path = token->id.built;
	tmp = separate_token(&token->id);
	if (token->index >= 0 && token->index != e_env.pipenum
		&& e_env.pipenum != 0)
		child_in(token, 1, envp, e_env);
	else if (token->index == e_env.pipenum && e_env.pipenum > 0)
		pipe_out(token, 1, envp, e_env);
	if (token->id.out != STDOUT_FILENO)
	{
		dup2(token->id.out, STDOUT_FILENO);
		close(token->id.out);
	}
	if (token->id.in != 0)
	{
		dup2(token->id.in, STDIN_FILENO);
		close(token->id.in);
	}
	execve(path, tmp, envp);
	perror("execve:");
	exit(errno);
	if (access(token->id.built, F_OK) != 0)
		exit(errno);
}

int	child_in(t_token *token, int i, char **envp, t_env e_env)
{
	if (token->index == 0)
	{
		close(token->fd[0]);
		dup2(token->fd[1], STDOUT_FILENO);
		close(token->fd[1]);
		close(token->next->fd[1]);
		close(token->next->fd[0]);
	}
	else
	{
		close(token->fd[0]);
		dup2(token->prev->fd[0], STDIN_FILENO);
		close(token->prev->fd[0]);
		close(token->prev->fd[1]);
		dup2(token->fd[1], STDOUT_FILENO);
		close(token->fd[1]);
		close(token->prev->fd[1]);
	}
	if (i == 1)
		return (0);
	else if (i == 0)
		return (builtins(token, envp, e_env));
	else
		return (errno);
}

int	pipe_out(t_token *token, int i, char **envp, t_env e_env)
{
	close(token->prev->fd[1]);
	dup2(token->prev->fd[0], STDIN_FILENO);
	close(token->prev->fd[0]);
	close(token->fd[0]);
	close(token->fd[1]);
	if (i == 1)
		return (0);
	else if (i == 0)
		return (builtins(token, envp, e_env));
	else
		return (errno);
}
