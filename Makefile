# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunghki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 19:50:41 by hyunghki          #+#    #+#              #
#    Updated: 2023/04/26 16:32:43 by hyunghki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
