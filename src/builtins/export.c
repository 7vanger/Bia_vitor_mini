/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:02:52 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:03:06 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_env(char *str, int i)
{
	char	*tmp;

	if (g_env.env[i])
		free(g_env.env[i]);
	tmp = ft_strdup(str);
	return (tmp);
}

char	**export_env(char *str)
{
	char	**var;
	int		i;
	int		j;

	i = 0;
	while (g_env.env[i] != NULL)
		i++;
	j = i;
	var = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (g_env.env[i] != NULL && i < j)
	{
		var[i] = ft_strdup(g_env.env[i]);
		free(g_env.env[i]);
		i++;
	}
	var[i] = ft_strdup(str);
	var[i + 1] = NULL;
	free(g_env.env);
	return (var);
}

int	export_comp(const char *str, char *var)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)str;
	b = (unsigned char *)var;
	j = ft_strlen(str);
	i = 0;
	while (i < j && a[i] != '=')
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

int	identchcker(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "=", 1) == 0)
		return (4);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+')
			return (4);
		if (str[i] == '-')
			return (4);
		i++;
	}
	return (0);
}

int	execute_export(char *str)
{
	char	**var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (identchcker(str) == 4)
		return (4);
	var = ft_split(str, ' ');
	while (var[j] != NULL)
	{
		while (g_env.env[i] && export_comp(var[j], g_env.env[i]) != 0)
			i++;
		if (g_env.env[i] == NULL)
			g_env.env = export_env(var[j]);
		else
			g_env.env[i] = new_env(var[j], i);
		j++;
	}
	free_pointers(var);
	return (errno);
}
