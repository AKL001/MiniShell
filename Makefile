NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
       src/syntax_checker/syntax_checker.c \
       src/syntax_checker/syntax_checker_utils.c\
	   src/syntax_checker/syntax_checker_utils2.c\
	   src/tokonizer/printf_tokens.c\
	   src/tokonizer/tokonizer_utils.c\
	   src/tokonizer/tokonizer.c
		src/built-in/built_exe.c\
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC)  $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline -lncurses -g

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
