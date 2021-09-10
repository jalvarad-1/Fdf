# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 15:45:28 by jalvarad          #+#    #+#              #
#    Updated: 2021/09/10 19:07:36 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

LNAME			= fdf_l

LIBFT			= libft.a

LIBFT_DIR		= ./Libft/

SRCS			= main.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror -fsanitize=address

LFLAGS			= -lmlx -lXext -lX11 -lm

MFLAGS			= -lmlx -framework OpenGL -framework AppKit

all: make-libft $(NAME)

lin: make-libft $(LNAME)

$(LNAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(LFLAGS) -o $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(MFLAGS) -o $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

make-libft:
		make -C $(LIBFT_DIR)

clean:
		rm -rf $(OBJS)
		$(MAKE) clean -C ./Libft

fclean: clean
		$(MAKE) fclean -C ./Libft
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean