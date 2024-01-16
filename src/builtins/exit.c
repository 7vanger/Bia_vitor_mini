/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:15 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:01:30 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isalnum_base(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i] != '\0')
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
		{
			i++;
			continue ;
		}
		if (str[i] != '\0' && ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_exit(t_token *token, char *status, t_env *l_env)
{
	int	i;

	write (2, "exit\n", 6);
	if (isalnum_base(status) == 2)
		i = 0;
	else if (isalnum_base(status) == 1)
	{
		ft_msg(3);
		i = 255;
	}
	else
		i = ft_atoi(status);
	close(token->fd[1]);
	close(token->fd[0]);
	free_buff(token);
	free_env(l_env);
	free(g_env.pwd);
	exit(i);
}
