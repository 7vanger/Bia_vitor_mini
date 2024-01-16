/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:12:21 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 18:49:42 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_finder(void)
{
	int	i;

	i = 0;
	while (g_env.env[i] != NULL && ft_strncmp(g_env.env[i], "PATH=", 5) != 0)
		i++;
	if (g_env.env[i] == NULL)
	{
		errno = 78;
		return (errno);
	}
	return (i);
}

char	*get_cmd(char **str, t_id *id)
{
	char	*tmp;
	int		i;
	char	*cmd;

	cmd = ft_strjoin("/", id->built);
	i = 0;
	while (str[i] != NULL)
	{
		tmp = ft_strjoin(str[i], cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(cmd);
			return (tmp);
		}
		i++;
		free(tmp);
	}
	free(cmd);
	return (NULL);
}

t_count	init_count(void)
{
	t_count	count;

	count.i = 0;
	count.j = 0;
	return (count);
}

char	**separate_token(t_id *id)
{
	char	**bin;
	char	**buff;
	t_count	count;

	count = init_count();
	if (id->print == NULL)
		return (ft_split(id->built, ' '));
	bin = ft_split(id->print, ' ');
	while (bin[count.i] != NULL)
		count.i++;
	buff = ft_calloc(count.i + 2, sizeof(char *));
	count.j = count.i + 2;
	count.i = 1;
	buff[0] = ft_strdup(id->built);
	while (bin[count.i - 1] != NULL)
	{
		buff[count.i] = ft_strdup(bin[count.i - 1]);
		count.i++;
	}
	while (count.i++ < (count.j - 1))
		buff[count.i] = NULL;
	free_pointers(bin);
	return (buff);
}

int	get_path(t_id *id, t_token *token, char **envp, t_env *l_env)
{
	int		i;
	char	**buff;
	char	*tmp;

	i = path_finder();
	if (i == errno)
		return (errno);
	tmp = ft_substr(g_env.env[i], 5, ft_strlen(g_env.env[i]));
	buff = ft_split(tmp, ':');
	free(tmp);
	tmp = get_cmd(buff, id);
	if (tmp == NULL)
		token->err = 5;
	free_pointers(buff);
	if (tmp == NULL)
		return (5);
	else
		return (exec_path(token, tmp, envp, l_env));
}
