# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 15:45:28 by jalvarad          #+#    #+#              #
#    Updated: 2021/09/12 12:30:24 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

LNAME			= fdf_l

LIBFT			= libft.a

LIBFT_DIR		= ./Libft/

SRCS			= fdf.c \
				error_and_exits.c \
				get_coordenates_init.c \
				get_lines_coords.c \
				get_nbrs_map.c \
				other_utils.c \
				parser_and_hexas.c \
				put_coords_good.c \
				utils.c \
				draw_map.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

LFLAGS			= -lmlx -lXext -lX11 -lm

MFLAGS			= -lmlx -framework OpenGL -framework AppKit

all: make_libft $(NAME)

lin: make_libft $(LNAME)

$(LNAME): $(OBJS) fdf.h
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(LFLAGS) -o $(NAME)

$(NAME): $(OBJS) fdf.h
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