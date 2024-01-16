/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:03:15 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:03:29 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(t_token *token, t_env *l_env)
{
	int	i;

	(void)l_env;
	i = 0;
	while (l_env->pwd[i] != '\0')
	{
		write (token->id.out, &l_env->pwd[i], 1);
		i++;
	}
	write (token->id.out, "\n", 1);
	return (errno);
}
