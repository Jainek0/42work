NAME = minishell

BONUS = minishell_bonus

CC = cc

CFLAGS = -ggdb -Wall -Werror -Wextra

INCLUDE = minishell.h

LIBS = ../ft_printf_fd/libftprintf_fd.a ../libft/libft.a

SRC =	minishell_cleanline.c \
	minishell_expand.c \
	minishell_expanding.c \
	minishell_getenv.c \
	minishell_liberator.c \
	minishell_main_parsing.c \
	minishell_parsing_is_checker.c \
	minishell_split_line.c \
	minishell_manage_line.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME):$(OBJ)
	@make -C ../libft/
	@make -C ../ft_printf_fd/
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBS) -l readline

$(BONUS): $(OBJ_BONUS)
	@make -C ../libft/
	@make -C ../ft_printf_fd/
	@$(CC) $(CFLAGS) $(SRC_BONUS) -o $(BONUS) $(LIBS) -l readline

all: $(NAME)

bonus: $(BONUS)

clean:
	@make clean -C ../ft_printf_fd/
	@make clean -C ../libft/
	@rm -rf $(OBJ) $(OBJ_BONUS)

fclean:	clean
	@make fclean -C ../ft_printf_fd/
	@make fclean -C ../libft/
	@rm -rf $(NAME) $(BONUS)

re:	fclean all

.PHONY:	all bonus clean fclean re
