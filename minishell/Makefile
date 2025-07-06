NAME		= minishell

SRC			= 	main.c	\
				\
				parsing/shell_parsing_is_checker.c	\
				parsing/shell_token_expand.c		\
				parsing/shell_manage_line.c			\
				parsing/shell_split_space.c			\
				parsing/shell_split_line.c			\
				parsing/shell_cleanline.c			\
				parsing/shell_expanding.c			\
				parsing/shell_liberator.c			\
				parsing/shell_tokenizer.c			\
				parsing/shell_parsing.c				\
				parsing/shell_envlen.c				\
				parsing/shell_expand.c				\
				\
				mini/built-in/mini_export_add.c	\
				mini/built-in/mini_export.c		\
				mini/built-in/mini_expand.c		\
				mini/built-in/mini_unset.c		\
				mini/built-in/mini_echo.c		\
				mini/built-in/mini_exit.c		\
				mini/built-in/mini_pwd.c		\
				mini/built-in/mini_cd.c			\
				\
				mini/mini_execve.c			\
				mini/mini_pipe.c			\
				mini/mini_red.c				\
				mini/mini_env.c				\
				\
				utils/liberate_all.c	\
				utils/short_check.c		\
				utils/utils_bis.c		\
				utils/utils_env.c		\
				utils/utils.c			\
				utils/lst.c				\
				utils/sig.c				\
				\
				set/set_data.c		\
				set/set_fork.c		\
				
OBJ			= $(SRC:.c=.o)

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a

CFLAGS		= -Werror -Wextra -Wall -g
LDFLAGS		= -I $(LIB_PATH)/ 

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIB) -l readline -o $(NAME)

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