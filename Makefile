# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 15:45:28 by jalvarad          #+#    #+#              #
#    Updated: 2021/08/15 15:45:30 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf.a

LIBFT			= ./Libft/libft.a

SRCS			= main.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C ./Libft
		cp	Libft/libft.a $(NAME)
		$(CC) $(CFLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS)
		gcc $(CFLAGS) $(NAME) -o fdf -fsanitize=address

clean:
		$(MAKE) clean -C ./Libft
		rm -f $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./Libft
		rm -f $(OBJS) $(NAME)
		rm -f push_swap

re: fclean all

.PHONY: all re m clean fclean bonus