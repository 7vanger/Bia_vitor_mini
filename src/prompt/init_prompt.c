/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:13:00 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:13:25 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sign(int sign)
{
	if (sign == SIGINT && g_env.shell_state == SH_CHILD)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (sign == SIGINT && g_env.shell_state == SH_READ)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign == SIGINT && g_env.shell_state == SH_EXEC)
		return ;
}

void	display_prompt(t_var *var)
{
	g_env.shell_state = SH_READ;
	var->cmd = readline(var->term);
	g_env.shell_state = SH_EXEC;
}

void	set_env(char **str, t_env *l_env)
{

	g_env.shell_state = SH_READ;
	g_env.retval = 0;


	l_env->env = set_env_2(str);
	l_env->child = 0;
	l_env->pwd = ft_substr(set(1, l_env), 4, ft_strlen(set(1, l_env)));
	l_env->home = ft_substr(set(2, l_env), 5, ft_strlen(set(2, l_env)));
}

void	init_prompt(t_var *var, char **env, t_env *l_env)
{
	set_env(env, l_env);
	var->term = "shellzinho$ ";
	var->cmd = NULL;
	var->fileno_out = STDIN_FILENO;
	var->func_term = isatty(var->fileno_out);
	if(var->func_term)
	{
		tcgetattr(var->fileno_out, &(*var).mod_term);
		(*var).new_opt = (*var).mod_term;
		(*var).new_opt.c_cc[VQUIT] = 0;
		tcsetattr(var->fileno_out, TCSANOW, &(*var).new_opt);
	}
	else
		perror("Not a terminal");
}
