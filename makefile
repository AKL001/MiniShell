src =   cleanup/clean_up.c \
		lexing/check_input.c \
		lexing/create_token.c \
		lexing/ft_split.c \
		lexing/ft_split_helper.c \
		lexing/handle_operator.c \
		lexing/handle_quotes.c \
		lexing/handle_word.c \
		lexing/tokenazation.c \
		lexing/trim_string.c \
		lexing/unclosed_quotes.c \
		parsing/parse_cmd.c \
		parsing/parse_utils.c \
		parsing/parse_utile_2.c \
		parsing/remove_quotes.c \
		parsing/redirection.c \
		expansion/expand_dollar.c \
		expansion/expand.c \
		expansion/split_value.c \
		expansion/expand_string.c \
		built-in/init_env.c \
		built-in/env.c \
		built-in/built_exe.c\
		built-in/cd.c\
		built-in/echo.c\
		built-in/pwd.c\
		built-in/unset.c\
		built-in/export.c\
		built-in/exit.c\
		built-in/export_helper.c\
		main.c \
		execution/exec_utils.c\
		execution/exec_utils2.c\
		execution/exec_utils3.c\
		execution/execute_command_line.c\
		execution/here_doc.c\
		execution/here_doc_utils.c\
		execution/get_next_line.c\
		execution/pipes.c\
		execution/redirection.c\
		syntax_checker/syntax_checker.c\
		syntax_checker/syntax_utils.c\
		syntax_checker/syntax_utils2.c\
		signals/signals.c\
		print_cmd.c

OBJ = $(src:.c=.o)
NAME = minishell
LIBFT_DIR = libft
libft = $(LIBFT_DIR)/libft.a
flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(libft)
	cc $(flags) $(OBJ) -o $(NAME) $(libft) -lreadline -g

$(libft):
	@make -C $(LIBFT_DIR)

%.o: %.c
	cc $(flags) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
