#include "minishell.h"

t_env g_env;

int	execute_mini(t_token *process, char **envp, t_env *l_env)
{
	t_token	*token;
	int		i;

	i = 0;
	token = process;
	while (i <= g_env.pipenum)
	{
		i++;
		if (is_builtin(process) == 0)
			pipers(process, envp, l_env);
		else if (is_builtin(process) != 0)
			builtins(process, envp, l_env);
		process = process->next;
	}
	i = 0;
	while (i <= g_env.pipenum)
	{
		close (token->fd[0]);
		close (token->fd[1]);
		wait(0);
		//free(token);
		token = token->next;
		i++;
	}
	g_env.pipenum = 0;
	l_env->pipenum = 0;
	return (0);
}

t_token	*init_process(t_var *var, t_token *process, char **envp, t_env *l_env)
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
		process = create_node(var->cmd, process, l_env);
		add_history(var->cmd);
		free(var->cmd);
		g_env.shell_state = SH_READ;
		if (process->next)
			return (process);
		else if (process != NULL)
			builtins(process, envp, l_env);
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
	t_env	*l_env;

	// atexit(report_mem_leak);

	(void)argv;
	process = NULL;
	l_env = malloc(sizeof(t_env));
	if (argc < 2)
	{
		init_prompt(&var, envp, l_env);
		while (1)
		{
			process = init_process(&var, process, envp, l_env);
			if (g_env.pipenum)
				execute_mini(process, envp, l_env);
		}
		return (errno);
	}
	errno = 5;
	return (errno);
}
