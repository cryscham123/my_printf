NAME= libftprintf.a
CFLAGS= -Wall -Werror -Wextra
SRCS= ft_printf.c \
	  parse.c \
	  flag_utils.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)

.PHONY: re clean fclean

re:
	make fclean
	make all

clean:
	rm -f *.o

fclean:
	make clean
	rm -f $(NAME)

$(NAME): $(OBJS)
	ar -rc $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
