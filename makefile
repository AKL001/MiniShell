src =   cleanup/clean_up.c \
		lexing/check_input.c \
		lexing/create_token.c \
		lexing/ft_split.c \
		lexing/handle_operator.c \
		lexing/handle_quotes.c \
		lexing/handle_word.c \
		lexing/tokenazation.c \
		lexing/trim_string.c \
		lexing/unclosed_quotes.c \
		parsing/parse_cmd.c \
		parsing/parse_utils.c \
		parsing/remove_quotes.c \
		parsing/redirection.c \
		expansion/assign_value.c \
		expansion/check_var.c \
		expansion/expande.c \
		built-in/init_env.c \
		built-in/env.c \
		built-in/built_exe.c\
		built-in/cd.c\
		built-in/echo.c\
		built-in/pwd.c\
		built-in/unset.c\
		built-in/export.c\
		main.c \
		print_cmd.c\
		execution/exec_utils.c\
		execution/exec_utils2.c\
		execution/execute_command_line.c\
		execution/here_doc.c\
		execution/get_next_line.c\
		execution/pipes.c\
		execution/redirection.c\
		syntax_checker/syntax_checker.c\
		syntax_checker/syntax_utils.c\
		syntax_checker/syntax_utils2.c\


obj = $(src:.c=.o)

name = shell
libft = libft/libft.a
flags = -g -Wall -Wextra -Werror

run: re
	@make clean
	# @clear
	@./$(name)

all: $(name)

$(name): $(obj) $(libft)
	cc  $(obj) -o $(name) $(libft) -lreadline

%.o: %.c
	cc  -c $< -o $@

# $(libft):
# 	@make -C libft/

clean:
	rm -f $(obj)
	@make -C libft/ clean

fclean: clean
	rm -f $(name)
	# @make -C libft/ fclean

re: fclean all
