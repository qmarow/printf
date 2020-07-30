NAME = libftprintf.a
HEAD = printf.h

SRCS =  printf.c \
				ft_atoi.c ft_isdigit.c \
				ft_memset.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_strdup.c \
				ft_strjoin.c ft_strlen.c \
				ft_strnstr.c ft_substr.c \
				ft_strchr.c parce.c \
				ft_handler.c ft_utils.c \
				ft_handler_w_ac.c \

OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEAD)
		gcc -c $< -o $@

all: $(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -f *.o
		rm -f *.o

fclean: clean
		rm -f $(NAME);

re: fclean all

.PHONY: all clean fclean re						