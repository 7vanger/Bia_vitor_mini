/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:05:05 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:05:20 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*do_history(char *str)
{
	if (str != NULL)
		free(str);
	str = readline("> ");
	if (!str)
		exit_prompt();
	return (str);
}

static int	sub_readline(char *str, char *delim)
{
	int		pipes[2];
	pid_t	child;

	pipe(pipes);
	child = fork();
	while (child == 0)
	{
		str = do_history(str);
		if (ft_strncmp(str, delim, ft_strlen(delim)) == 0)
		{
			free(str);
			close(pipes[1]);
			exit(0);
		}
		if (str[0] == '\0' || ft_strcmp(str, "\n") == 0)
			continue ;
		write (pipes[1], str, ft_strlen(str));
		write (pipes[1], "\n", 1);
	}
	close (pipes[1]);
	free (delim);
	if (child != 0)
		wait (0);
	return (pipes[0]);
}

int	here_doc(int i, t_token *token)
{
	char	*delim;
	char	*str;
	int		c;

	cut_1(1, token);
	if (token_limit(token->input[0]) == 1 || token->input[0] == '\0')
		return (token->err = 1);
	c = delimeter_token(i, token->input);
	if (token->input[0] == '\0' || token->input[0] == '|')
		return (token->err = 2);
	str = NULL;
	printf("-> fffff\n"); //TESTE
	delim = ft_substr(token->input, 0, c);
	if (ft_isprint(delim[0]) == 0)
		return (2);
	token->input += c - 1;
	return (sub_readline(str, delim));
}

int	input_token(int i, t_token *token)
{
	int		file;
	char	*tmp;

	cut_1(0, token);
	if (token_limit(token->input[0]) == 1 || token->input[0] == '\0')
		return (token->err = 1);
	printf("-> eeeeee\n"); //TESTE
	tmp = ft_substr(token->input, 0, count_until_char(token->input, i));
	tmp = cut_char(tmp, 39);
	tmp = cut_char(tmp, 34);
	token->input = cut_space(token->input);
	file = open(tmp, O_RDONLY);
	return (set_file(file, tmp, token));
}

int	output_token(int i, t_token *token, int code)
{
	int		file;
	char	*tmp;

	file = 0;
	if (token->id.out != STDOUT_FILENO)
		close(token->id.out);
	cut_1(code, token);
	if (token_limit(token->input[0]) == 1 || token->input[0] == '\0')
		return (token->err = 1);
	tmp = sub_trim(i, token);
	if (code == 0)
		file = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (code == 1)
		file = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (file == -1)
	{
		token->id.out = file;
		free(tmp);
		return (1);
	}
	token->input = cut_space(token->input);
	token->id.out = file;
	free(tmp);
	return (0);
}
