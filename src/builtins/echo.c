/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:00:21 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:00:39 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_echo(t_id id)
{
	int		i;
	char	c;

	i = 0;
	c = '\n';
	if (ft_strncmp(id.opt, "-n", 2) == 0)
	{
		while (id.print && id.print[i] != '\0')
		{
			write(id.out, &id.print[i], 1);
			i++;
		}
	}
	else
	{
		while (id.print && id.print[i] != '\0')
		{
			write(id.out, &id.print[i], 1);
			i++;
		}
		if (errno != 2)
			write(id.out, &c, 1);
	}
	return (errno);
}
