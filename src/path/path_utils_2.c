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
	return (status);
}

int	old_pipers(t_token *process, char **envp, pid_t child)
{
	int		r;
	//int		i;

	r = 0;
	//i = 0;
	if (child == 0)
	{
		fprintf(stderr, "Pipers %s\n", process->id.built);
		if (process->next)
			r = child_in(process, 0, envp);
		else if (!process->next)
			r = pipe_out(process, 0, envp);
		fprintf(stderr, "FIM PIPERS\n");
		//close_fds_in_child(process);
		//return (execve(process->id.built, separate_token(&process->id), envp));
		//exit(r);
		process = process->next;
	}
	else if (child < 0)
	{
		perror("fork");
		exit(1);
	}
	return (g_env.retval = r);
}

int count(t_token *token) {
	int i;
	i = 0;
	while (token)
	{
		i++;
		token = token->next;

	}
	return i;
}

int	pipers(t_token *token, char **envp, pid_t child)
{
	int i = 0;
  	pid_t pid;

	(void)child;
	(void)envp;
 	int cmd_len = g_env.pipenum + 1;
	t_token *tmp = token;
	while( i < cmd_len)
	{
		fprintf(stderr, "cmd: %s\n", token->id.built);
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			for (int j = 0; j < cmd_len; j++) {
                if (j != token->index) {
                    close(token->fd[0]);
                    close(token->fd[1]);
                }
            }

			if (token->next != NULL)
			{
				if (dup2(token->fd[1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(token->fd[1]);
			};
			if (token->index != 0)
			{
				if (dup2(token->prev->fd[0], 0) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
        		}
				close(token->prev->fd[0]);
                close(token->prev->fd[1]);
      		}
			//close_fds_in_child(token);
			if (execve(token->id.built, separate_token(&token->id), NULL) < 0)
			{
				perror(token->id.built);
				exit(EXIT_FAILURE);
			}

    	}
		else
		{
			// Se não for o último comando, fechar o descritor de escrita
            if (token->index != (cmd_len - 1)) {
                close(token->fd[1]);
            }
    	}

		i++;
		token = token->next;

	}

	i = 0;

	token = tmp;
	while (token->next)
	{
		close(token->fd[0]);
		close(token->fd[1]);
		token = token->next;
	}
:
	for (i = 0; i < cmd_len; i++)
		wait(NULL);

	return (0);

}	
