#include "minishell.h"

t_env g_env;

int	old_execute_mini(t_token *process, char **envp)
{
	t_token	*token;
	int		i;
	int status;
	pid_t	*child;
	//t_token *next_token;

	i = 0;
	status = 0;
	child = malloc(sizeof(pid_t) * (g_env.pipenum + 1));
	token = process;
	while (i <= g_env.pipenum)
	{
		child[i] = fork();
		if (child[i] == 0) {
			pipers(process, envp, child[i]);
			exit(0);
		}
		//pipeline(process, separate_token(&process->id), envp);
		process = process->next;
		i++;
	}
	i = 0;
	while (i <= g_env.pipenum)
	{
		fprintf(stderr, ">P. %d fechado   .2\n", i);
		close (token->fd[0]);
		close (token->fd[1]);
		//next_token = token->next;
		//free(token);
		token = token->next;
		i++;
	}
	i = 0;
	while (i <= g_env.pipenum)
	{
		waitpid(child[i], &status, 0);
		i++;
	}
	//for (i = 0; i <= g_env.pipenum; i++) wait(NULL);
	g_env.pipenum = 0;
	return (0);
}

int	execute_mini(t_token *process, char **envp)
{
	
	pipers(process, envp, 0);
	
	return (0);
}

t_token	*init_process(t_var *var, t_token *process, char **envp)
{
	while (var->func_term)
	{
		signal(SIGINT, handle_sign);
		display_prompt(var);
		if (!var->cmd)
			exit_prompt();
		if (var->cmd[0] == '\0' || ft_strcmp(var->cmd, "\n") == 0
				|| ft_isspace_2(var->cmd) == 1)
		{
			free(var->cmd);
			continue ;
		}
		process = create_node(var->cmd, process);
		add_history(var->cmd);
		free(var->cmd);
		g_env.shell_state = SH_READ;
		if (process->next)
			return (process);
		else if (process != NULL)
			builtins(process, envp);
		else if (process == NULL)
			break ;
		free(process);
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp) 
{
	t_var	var;
	t_token	*process;

	// atexit(report_mem_leak);

	(void)argv;
	process = NULL;
	if (argc < 2)
	{
		init_prompt(&var, envp);
		while (1)
		{
			process = init_process(&var, process, envp);
			if (g_env.pipenum)
				execute_mini(process, envp);
				//pipeline(process, separate_token(&process->id), envp);
		}
		return (errno);
	}
	errno = 5;
	return (errno);
}
