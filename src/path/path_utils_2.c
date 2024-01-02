/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sous <ade-sous@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:11:55 by vlopes            #+#    #+#             */
/*   Updated: 2024/01/02 08:18:52 by ade-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_path(t_token *token, char *path, char **envp, t_env e_env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(token, path, envp, e_env);
	else if (child != 0 && token->index > 0)
	{
		close(token->prev->fd[1]);
		close(token->prev->fd[0]);
	}
	else if (child != 0 && token->index == e_env.pipenum && e_env.pipenum != 0)
		close(token->prev->fd[1]);
	if (child != 0)
	{
		e_env.shell_state = SH_CHILD;
		waitpid(0, &status, 0);
	}
	if (token->id.in != STDIN_FILENO)
		close(token->id.in);
	if (token->id.out != STDOUT_FILENO)
		close(token->id.out);
	free(path);
	return (errno);
}

int	pipers(t_token *process, char **envp, t_env e_env)
{
	pid_t	parent;
	int		r;

	r = 0;
	parent = fork();
	if (parent == 0)
	{
		if (process->next)
			r = child_in(process, 0, envp, e_env);
		else if (!process->next)
			r = pipe_out(process, 0, envp, e_env);
		exit(r);
	}
	else if (parent < 0)
	{
		perror("fork");
		exit(1);
	}
	else
		wait(0);
	return (e_env.retval = r);
}	
