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

int	exec_path(t_token *token, char *path, char **envp)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(token, path, envp);
	else if (child != 0 && token->index > 0)
	{
		close(token->prev->fd[1]);
		close(token->prev->fd[0]);
	}
	else if (child != 0 && token->index == g_env.pipenum && g_env.pipenum != 0)
		close(token->prev->fd[1]);
	if (child != 0)
	{
		g_env.shell_state = SH_CHILD;
		waitpid(0, &status, 0);
	}
	if (token->id.in != STDIN_FILENO)
		close(token->id.in);
	if (token->id.out != STDOUT_FILENO)
		close(token->id.out);
	free(path);
	return (errno);
}

void	father_in_first_node(t_token *token) {
	if (token->index == 0)
	{
		fprintf(stderr, "\n>> P. %d: Fechando leitura\n", token->index);
		close(token->fd[0]);
	}
	else
	{
		fprintf(stderr, "\n>> P. %d: Fechando escrita\n", token->prev->index);
		close(token->prev->fd[1]);
		fprintf(stderr, ">> P. %d: Fechando leitura\n", token->index);
		close(token->fd[0]);
	}
}

void	father_in_last_node(t_token *token) {
	fprintf(stderr, "\n>> P. %d: Fechando escrita\n", token->prev->index);
	close(token->prev->fd[1]);
	fprintf(stderr, ">> P. %d: Fechando leitura\n", token->index);
	close(token->fd[0]);
	fprintf(stderr, ">> P. %d: Fechando escrita\n", token->index);
	close(token->fd[1]);
}

int	pipers(t_token *process, char **envp)
{
	pid_t	parent;
	int		r;

	r = 0;
	parent = fork();
	if (parent == 0)
	{
		if (process->next)
			r = child_in(process, 0, envp);
		else if (!process->next)
			r = pipe_out(process, 0, envp);
		exit(r);
	}
	else if (parent < 0)
	{
		perror("fork");
		exit(1);
	}
	else {
		if (process->next)
			father_in_first_node(process);
		else if (!process->next)
			father_in_last_node(process);
		wait(0);
	}
	return (g_env.retval = r);
}	
