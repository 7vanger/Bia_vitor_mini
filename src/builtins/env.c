/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:00:46 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:01:05 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_env *l_env)
{
	int	i;
	int	j;

	(void)l_env;
	i = 0;
	j = -1;
	while (l_env->env[i] != NULL)
		i++;
	while (++j < i)
		printf ("%s\n", l_env->env[j]);
	return (errno);
}
