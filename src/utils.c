/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:31 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:06:46 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buff(t_token *token)
{
	if (token->id.print)
		free (token->id.print);
	if (token->id.built)
		free (token->id.built);
	if (token->id.path)
		free (token->id.path);
	free (token->id.opt);
	return ;
}

void	exit_prompt(void)
{
	write(0, "exit\n", 6);
	exit(EXIT_SUCCESS);
}

void	free_pointers(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_msg(int code)
{
	if (code == errno)
		return (code);
	if (code == 1)
		write(2, "minishell: incorrect use of a token\n", 37);
	if (code == 2)
		write(2, "minishell: no such file or directory\n", 38);
	if (code == 3)
		write(2, "minishell: exit: numeric argument required\n", 44);
	if (code == 4)
		write(2, "minishell: export: invalid identifier\n", 39);
	if (code == 5)
		write(2, "minishell: command not found\n", 30);
	return (code);
}

int	ft_isspace_2(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == 'f' || str[i] == 'r'
			|| str[i] == ' '))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}
