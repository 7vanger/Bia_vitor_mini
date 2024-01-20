/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:04:37 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:04:51 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_1(int code, t_token *token)
{
	if (code == 0)
		token->input += 1;
	if (code == 1)
		token->input += 2;
	token->input = cut_space(token->input);
}

char	*cut_char(char *file, char c)
{
	int		i;
	int		j;
	char	*cpy;
	char	*real;

	i = 0;
	j = 0;
	cpy = ft_calloc(ft_strlen(file), sizeof(char));
	while (file[i])
	{
		while (file[i] == c)
			i++;
		cpy[j] = file[i];
		i++;
		j++;
	}
	cpy[j] = '\0';
	real = ft_strdup(cpy);
	free(cpy);
	free(file);
	return (real);
}

int	set_file(int file, char *tmp, t_token *token)
{
	char	*read;

	if (file == -1)
	{
		free(tmp);
		token->id.in = file;
		return (1);
	}
	if (ft_strncmp(token->id.built, "cd", 2) == 0)
	{
		read = ft_readline(file, 1, NULL);
		token->id.path = ft_strdup(read);
		free(read);
		close(file);
	}
	else if (is_builtin(token) != 0)
		token->id.in = file;
	free(tmp);
	return (0);
}

char	*sub_trim(int i, t_token *token)
{
	char	*tmp;
	int		j;

	j = cut_until_char(token->input, i);
	tmp = ft_substr(token->input, 0, j);
	if (j > delimeter_token(i, tmp))
	{
		j = delimeter_token(i, tmp);
		free(tmp);
		tmp = ft_substr(token->input, 0, j);
	}
	tmp = cut_char(tmp, 34);
	tmp = cut_char(tmp, 39);
	return (tmp);
}
