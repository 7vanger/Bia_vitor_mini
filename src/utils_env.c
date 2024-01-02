/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:58 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:07:10 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_env_2(char **env)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = -1;
	while (env[i])
		i++;
	buff = ft_calloc(i + 1, sizeof(char *));
	while (++j < i)
		buff[j] = ft_strdup(env[j]);
	buff[j] = NULL;
	return (buff);
}

char	*set(int num, t_env e_env)
{
	int	i;

	i = 0;
	if (num == 1)
	{
		while (e_env.env[i] && ft_strncmp(e_env.env[i], "PWD=", 4) != 0)
			i++;
	}
	else if (num == 2)
	{
		while (e_env.env[i] && ft_strncmp(e_env.env[i], "HOME=", 5) != 0)
			i++;
	}
	return (e_env.env[i]);
}
