NAME = libftprintf.a
HEAD = printf.h

SRCS =  printf.c \
				ft_atoi.c ft_isdigit.c \
				ft_memset.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_strdup.c \
				ft_strjoin.c ft_strlen.c \
				ft_strnstr.c \

OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEAD)
		gcc -Wall -Wextra -Werror -c $< -o $@

all: $(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -f *.o
		rm -f *.o

fclean: clean
		rm -f $(NAME);

re: fclean all

.PHONY: all clean fclean re						