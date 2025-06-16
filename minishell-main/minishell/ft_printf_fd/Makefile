NAME = libftprintf_fd.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = ft_printf_fd.h

SRC =	ft_printf_fd.c \
	ft_printf_fd_parts.c \

OBJ = $(SRC:.c=.o)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rcs $(NAME) $^

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean:	clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY:	clean fclean re bonus
