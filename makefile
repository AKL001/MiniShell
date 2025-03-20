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
		parsing/redirection.c \
		main.c \
		print_cmd.c

obj = $(src:.c=.o)

name = shell
libft = libft/libft.a
flags = -g -Wall -Wextra -Werror

run: re
	@make clean
	@clear
	@./$(name)

all: $(name)

$(name): $(obj) $(libft)
	cc $(flags) $(obj) -o $(name) $(libft) -lreadline

%.o: %.c
	cc $(flags) -c $< -o $@

# $(libft):
# 	@make -C libft/

clean:
	rm -f $(obj)
	@make -C libft/ clean

fclean: clean
	rm -f $(name)
	# @make -C libft/ fclean

re: fclean all
