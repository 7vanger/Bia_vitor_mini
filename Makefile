CC = cc
FLAGS = -Werror -Wextra -Wall -g 
INC = -I./include
VPATH = src src/prompt src/libft_v src/parser src/builtins src/expand src/path\

PROMPT = init_prompt
LIBFT_V = get_next_line_utils ft_split ft_memcpy ft_strncmp ft_strcmp ft_isspace ft_ulstr ft_strdup ft_memset ft_calloc ft_isalnum ft_isprint ft_atoi\
		ft_substr ft_strjoin utils_libft ft_itoa ft_isdigit
PARSER = parser  utils_parser utils_parser2 utils_parser3
BUILTINS = builtins echo cd pwd export unset exit env
EXPAND = expand expand_utils
PATH_V = execute_path path_utils path_utils_2

NAME = minishell
SRC = $(addsuffix .c, $(PROMPT))\
	  $(addsuffix .c, $(LIBFT_V))\
	  $(addsuffix .c, $(PARSER))\
	  $(addsuffix .c, $(BUILTINS))\
	  $(addsuffix .c, $(EXPAND))\
	  $(addsuffix .c, $(PATH_V))\
	  utils_env.c utils.c create_node.c utils2.c here_doc.c cut.c read_line.c\
	  main.c

OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  -lreadline -o minishell

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all	

#run: re
#	./minishell

.PHONY: all clean fclean re run
