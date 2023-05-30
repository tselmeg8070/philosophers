# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 16:51:42 by tadiyamu          #+#    #+#              #
#    Updated: 2023/05/30 20:29:35 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main \
		ft_atoi_check \
		ft_atoi \
		philo_actions \
		philo_loop \
		philo_loop_conditions \
		philo_free \
		philo_print \
		philo_parser

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: re fclean all clean
