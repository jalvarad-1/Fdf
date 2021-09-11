# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 15:45:28 by jalvarad          #+#    #+#              #
#    Updated: 2021/09/11 11:43:31 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

LNAME			= fdf_l

LIBFT			= libft.a

LIBFT_DIR		= ./Libft/

SRCS			= main.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

LFLAGS			= -lmlx -lXext -lX11 -lm

MFLAGS			= -lmlx -framework OpenGL -framework AppKit

all: make_libft $(NAME)

lin: make_libft $(LNAME)

$(LNAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(LFLAGS) -o $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(MFLAGS) -o $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

make_libft:
		make -C $(LIBFT_DIR)

clean:
		rm -rf $(OBJS)
		$(MAKE) clean -C ./Libft

fclean: clean
		$(MAKE) fclean -C ./Libft
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean