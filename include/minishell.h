#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
/*# define SH_READ
# define SH_EXEC
# define SH_CHILD*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <termios.h>
# include <errno.h>
#include "leak_detector_c.h"

typedef struct	s_var
{
	char		*cmd;
	char		*term;
	int			fileno_out;
	int			func_term;
	struct termios	mod_term;
	struct termios	new_opt;
}				t_var; //(mini)

enum	state
{
	SH_READ,
	SH_EXEC,
	SH_CHILD,
};

typedef struct s_count
{
	int	i;
	int	j;
}		t_count;


typedef struct s_id
{
	char	*built;
	char	*opt;
	int		in;
	int		out;
	char	*print;
	char	*path;
	char	*tmp;
}			t_id; //(cmd)

typedef struct s_token
{
	char	*input;
	int		index;
	int		fd[2];
	int		err;
	t_id	id;
	struct s_token *next;
	struct s_token *prev;
}			t_token; //(node)

typedef struct s_env
{
	char		**env;
	char		**envp;
	char		*pwd;
	char		*home;
	int		retval;
	int		pipenum;
	pid_t		child;
	enum state	shell_state;
}				t_env; //data
				       
extern	t_env g_env;

t_token	*init_process(t_var *var, t_token *process, char **envp);

//prompt
void	init_prompt(t_var *var, char **env);
void	display_prompt(t_var *var);
void	set_env(char **env);

//utils
void	free_buff(t_token *token);
void	exit_prompt(void);
void	free_pointers(char **str);
int	ft_msg(int code);
int	ft_isspace_2(char *str);

//parser
void	parser(t_token *token);
void	if_builtin(int i, t_token *token);
void	if_printf(int i, t_token *token);
void	if_opt(t_token *token);
void	if_token(t_token *token);
void	handle_quote(t_token *token, int i);
int	cut_until_char(char *str, char c);
char	*paste_char(char *str, char *new);
void	process_Input_Token(t_token *token, int i);
int	scam_for_word(char *input);
int	token_limit(char c);
int	delimeter_token(int i, char *str);
void	any_path(t_token *token);
void	direct_path(t_token *token);
void	home_path(t_token *token);

//builtins
int	builtins(t_token *token, char **envp);
void	add_section(t_token *token);
void	remove_section(t_token *token);
int	execute_echo(t_id id);
int	execute_cd(t_id id);
int	execute_pwd(t_token *token);
int	execute_export(char *str);
int	execute_unset(char *str);
int	execute_env(void);
void	free_env(void);
int	execute_exit(t_token *token, char *status);
int	is_builtin(t_token *token);
int	cut_before_first_char(char *input, char c);

//uitls_env
char	**set_env_2(char **env);
char	*set(int num);

//create node
t_token	*create_node(char *cmd, t_token *token);
t_token	*go_node(t_token *token);
void	set_token(t_token *token);

//utils2
char	*cut_space(char *token);
char	*clear_word(int i, char *input);
int	count_until_char(char *input, int i);
void	free_pointers_2(char **str, int i);

//main
void	handle_sign(int sign);
void	cut_1(int code, t_token *token);
char	*cut_char(char *file, char c);
int	set_file(int file, char *tmp, t_token *token);
char	*ft_readline(int fd, int num, char *delim);
char	*sub_trim(int i, t_token *token);

//expand
char	*expand(char *str, int i);
char	*add_content(char *content, char *add, int pos, char *var);
int	skip_single_quote(char *str, int i);

//path and pipe
int	execute_path(t_token *token, char **envp);
int	exec_parent(t_token *token, char **envp);
void	exec_child(t_token *token, char *path, char **envp);
int	child_in(t_token *token, int i, char **envp);
int	pipe_out(t_token *token, int i, char **envp);
char	**separate_token(t_id *id);
t_count	init_count(void);
int	get_path(t_id *id, t_token *token, char **envp);
char	*get_cmd(char **str, t_id *id);
int	path_finder(void);
int	exec_path(t_token *token, char *path, char **envp);
int	pipers(t_token *process, char **envp);

//heredoc
int	input_token(int i, t_token *token);
int	here_doc(int i, t_token *token);
int	output_token(int i, t_token *token, int code);

#endif
