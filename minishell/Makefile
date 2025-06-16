NAME		= minishell

SRC			= 	main.c \
				mini_echo.c	\
				mini_pwd.c	 \
				mini_cd.c	  \
				mini_execve.c \
				mini_env.c		 \
				utils_env.c\
				tmp.c		\
				liberate_all.c\
				utils.c \
				set_data.c

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