/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:07:45 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:47:22 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*print_var(char *str, t_env *l_env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strncmp(str, "?=", 2) == 0)
	{
		tmp = ft_itoa(g_env.retval);
		free(str);
		return (tmp);
	}
	while (l_env->env[i] && ft_strncmp(l_env->env[i], str, ft_strlen(str)) != 0)
		i++;
	if (l_env->env[i] != NULL)
		tmp = ft_substr(l_env->env[i], ft_strlen(str),
				ft_strlen(l_env->env[i]));
	else
		tmp = ft_calloc(1, sizeof(char));
	free (str);
	return (tmp);
}

static char	*retire_sign(char *str, int code)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (code == 0)
	{
		while (str[i] != '$')
			i++;
	}
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i + 1];
		i++;
	}
	new_str[i] = '=';
	i++;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static char	*remove_token(char *str, int i, int m)
{
	int		j;
	int		k;
	int		s;
	char	*rec;

	j = 0;
	k = 0;
	s = m - i;
	rec = ft_calloc(ft_strlen(str) - (s) + 1, sizeof(char));
	while (str[k] != '\0')
	{
		if (j == i)
			k = m;
		rec[j] = str[k];
		j++;
		k++;
	}
	rec[j] = '\0';
	free(str);
	return (rec);
}

static char	*find_expand(char *str, int i, t_env *l_env)
{
	int		m;
	char	*rec;
	char	*key;

	m = i;
	while (str[m] > 32 && str[m] != 34 && str[m] != '=' && str[m] != 39)
	{
		m++;
		if (str[m] == '$' || (str[m] == '?' && (m - i) == 1))
		{
			if (str[m] == '?' && (m - i) == 1)
				m++;
			break ;
		}
	}
	rec = ft_substr(str, i, m - i);
	key = print_var(retire_sign(rec, 1), l_env);
	rec = ft_substr(str, i, m - i);
	if (!*key)
		str = remove_token(str, i, m);
	else
		str = add_content(str, key, i, rec);
	free(key);
	free(rec);
	return (str);
}

char	*expand(char *str, int i, t_env *l_env)
{
	while (str[i] != '\0')
	{
		while (str[i] == '$')
		{
			if (str[i] == '$' && str[i + 1] == '\0')
				break ;
			if (str[i] == '$' && str[i + 1] == ' ')
				break ;
			if (str[i] == '$' && str[i + 1] == '=')
				break ;
			if (str[i] == '$' && str[i + 1] == 34)
				break ;
			
			str = find_expand(str, i, l_env);
		}
		if (str[i] == 39 && str[i-1] != 34)
		{
			i = skip_single_quote(str, i);
			if (str[i] == '\0')
				break ;
			else
				continue ;
		}
		i++;
	}
	return (str);
}
