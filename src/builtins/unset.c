/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:03:37 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:45:27 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_comp(const char *str, char *var)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)str;
	b = (unsigned char *)var;
	j = ft_strlen(str);
	i = 0;
	while (i < j)
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

void	free_env(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_env.env[i] != NULL)
		i++;
	while (j < i)
	{
		free(g_env.env[j]);
		j++;
	}
	free(g_env.env);
}

char	**env_unset(char *str)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	j = 0;
	while (g_env.env[i] != NULL)
		i++;
	var = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (g_env.env[i] != NULL)
	{
		if (unset_comp(str, g_env.env[i]) == 0)
			i++;
		if (g_env.env[i] == NULL)
			break ;
		var[j] = ft_strdup(g_env.env[i]);
		i++;
		j++;
	}
	free_env();
	var[j] = NULL;
	return (var);
}

int	execute_unset(char *str)
{
	char	**var;
	int		i;
	int		j;

	var = ft_split(str, ' ');
	i = 0;
	while (var[i] != NULL)
	{
		j = 0;
		while (g_env.env[j] != NULL)
		{
			if (ft_strncmp(var[i], g_env.env[j], ft_strlen(var[i])) == 0)
			{
				g_env.env = env_unset(var[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	free_pointers(var);
	return (errno);
}
