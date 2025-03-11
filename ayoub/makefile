SRC =	init_env.c \
		built_exe.c \
		built-in/echo.c \
		built-in/export.c \
		built-in/env.c \
		built-in/unset.c \
		built-in/cd.c \
		built-in/pwd.c \
		main.c 

OGJ = $(SRC:.c=.o)

NAME = shell
libft = Libft/libft.a

# FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OGJ) $(libft)
	cc -g $(FLAGS) $(OGJ) -o $(NAME) $(libft) -lreadline

$(libft) :
	@make -C Libft/

%.o : %.c
	cc $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OGJ)
	@make clean -C Libft/
fclean : clean
	rm -f $(NAME) $(libft)

re: fclean all