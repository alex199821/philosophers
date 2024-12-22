# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/22 16:08:14 by macbook           #+#    #+#              #
#    Updated: 2024/12/22 16:09:22 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAKE_LIB = ar -rcs

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C fclean

re: fclean all

.PHONY: all clean fclean re