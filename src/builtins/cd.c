/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:59:44 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:44:30 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_section(t_token *token)
{
	int		i;
	char	*buff;

	i = cut_before_first_char(token->id.tmp, '/');
	if (i == 0)
		i = 1;
	buff = ft_substr(token->id.tmp, 0, i);
	printf("consigo aqui\n");
	if (buff[0] == '/' && token->id.path[ft_strlen(token->id.path) - 1] == '/')
	{
		free(buff);
		token->id.tmp++;
		return ;
	}
	token->id.path = paste_char(token->id.path, buff);
	printf ("outra parte aqui id.path: %s\n", token->id.path);
	while (i--)
		token->id.tmp++;
	if (buff != NULL)
		free(buff);
}

void	remove_section(t_token *token)
{
	int		index;
	char	*tmp;

	index = 0;
	if (token->id.path[ft_strlen(token->id.path) - 1] == '/')
		index = 1;
	while (token->id.path[ft_strlen(token->id.path) - index - 1] != '/')
		index++;
	index = ft_strlen(token->id.path) - index;
	tmp = ft_substr(token->id.path, 0, index);
	free(token->id.path);
	token->id.path = ft_strdup(tmp);
	index = 2;
	while (index--)
		token->id.tmp++;
	free(tmp);
}

int	execute_cd(t_id id, t_env *l_env)
{
	char	*pwd;
	char	*oldpwd;

	(void)l_env;
	if (chdir(id.path) == -1)
	{
		write(2, "minishell: No such file or directory\n", 38);
		return (2);
	}
	pwd = ft_strjoin("OLDPWD=", l_env->pwd);
	execute_export(pwd, l_env);
	free(l_env->pwd);
	if (id.path[ft_strlen(id.path) - 1] == '/')
	{
		oldpwd = ft_substr(id.path, 0, ft_strlen(id.path) - 1);
		l_env->pwd = ft_strdup(oldpwd);
		l_env->pwd = ft_strdup(oldpwd);
		free(oldpwd);
	}
	else
	{
		l_env->pwd = ft_strdup(id.path);
	}
	free(pwd);
	pwd = ft_strjoin("PWD=", l_env->pwd);
	execute_export(pwd, l_env);
	free(pwd);
	return (errno);
}
