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

int	execute_env(void)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (g_env.env[i] != NULL)
		i++;
	while (++j < i)
		printf ("%s\n", g_env.env[j]);
	return (errno);
}
