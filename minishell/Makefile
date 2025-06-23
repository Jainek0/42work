NAME		= minishell

SRC			= 	main.c	\
				tmp.c	\
				\
				mini/built-in/mini_cd.c		\
				mini/built-in/mini_echo.c	\
				mini/built-in/mini_export.c	\
				mini/built-in/mini_pwd.c	\
				mini/built-in/mini_expand.c	\
				\
				utils/liberate_all.c	\
				utils/short_check.c		\
				utils/utils_env.c		\
				utils/utils.c			\
				\
				mini/mini_execve.c	\
				mini/mini_red.c		\
				mini/mini_env.c	\
				\
				set/set_data.c	\
				set/set_fork.c	\
				\

OBJ			= $(SRC:.c=.o)

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a

CFLAGS		= -Werror -Wextra -Wall -g
LDFLAGS		= -I $(LIB_PATH)/ 

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIB) -lreadline -o $(NAME)

$(LIB):
	make -sC $(LIB_PATH)

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make -sC $(LIB_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -sC $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re 