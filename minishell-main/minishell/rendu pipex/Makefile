NAME = pipex

BONUS = pipex_bonus

CC = cc

CFLAGS = -ggdb -Wall -Werror -Wextra

INCLUDE = pipex.h

LIBS = libft/libft.a

SRC =		pipex_source.c \
		pipex_utils.c \
		pipex_main.c \

SRC_BONUS =	pipex_source.c \
		pipex_utils.c \
		pipex_main_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME):$(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) libft/libft.a

$(BONUS): $(OBJ_BONUS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(SRC_BONUS) -o $(BONUS) libft/libft.a

all: $(NAME)

bonus: $(BONUS)

clean:
	@make clean -C libft/
	@rm -rf $(OBJ) $(OBJ_BONUS)

fclean:	clean
	@make fclean -C libft/
	@rm -rf $(NAME) $(BONUS)

re:	fclean all

.PHONY:	all bonus clean fclean re
