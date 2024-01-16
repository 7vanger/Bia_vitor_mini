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

int	call_wait(t_env *l_env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i <= l_env->pipenum)
	{
		g_env.shell_state = SH_CHILD;
		waitpid(0, &status, 0);
		i++;
	}
	return (status);
}

int	exec_path(t_token *token, char *path, char **envp, t_env *l_env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(token, path, envp, l_env);
	else if (child != 0 && token->index > 0)
	{
		close(token->prev->fd[1]);
		close(token->prev->fd[0]);
	}
	else if (child != 0 && token->index == l_env->pipenum
		&& l_env->pipenum != 0)
		close(token->prev->fd[1]);
	if (child != 0 && !token->next)
		status = call_wait(l_env);
	if (token->id.in != STDIN_FILENO)
		close(token->id.in);
	if (token->id.out != STDOUT_FILENO)
		close(token->id.out);
	free(path);
	return (status);
}

int	pipers(t_token *process, char **envp, t_env *l_env)
{
	pid_t	parent;
	int		r;

	r = 0;
	parent = fork();
	if (parent == 0)
	{
		if (process->next)
			r = child_in(process, 0, envp, l_env);
		else if (!process->next)
			r = pipe_out(process, 0, envp, l_env);
		exit(r);
	}
	else if (parent < 0)
	{
		perror("fork");
		exit(1);
	}
	else
		wait(0);
	return (g_env.retval = r);
}
