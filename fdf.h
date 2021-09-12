/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:02:16 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:25:07 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct s_program
{
	void	*mlx;
	void	*mlx_win;
}t_program;

typedef struct s_data
{
	void	*img;
	char	*ptr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_tools_map
{
	int			fd;
	char		*all_map;
	char		**split;
	int			s_row;
	int			s_aux;
	int			i;
	int			nbr_row;
	long int	**map;
	long int	*colors;
}t_tools_map;

typedef struct s_get_coord
{
	int			a;
	int			b;
	int			x;
	int			y;
	int			x_init;
	int			y_init;
	int			scale;
	int			s_aux;
	int			x_aux;
	int			color;
	int			c;
	int			d;
	int			i;
	int			j;
	float		xinc;
	float		yinc;
	long int	**array;
}t_get_coord;

void		ft_error(void);
void		iso(int *x, int *y, int z);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		del_map(long int **split, int nbr_row);
void		del_split(char **split);
int			absolute(int x);
void		del_str(char *str);
int			ft_close_win(t_program *i);
int			ft_key(int keycode);
void		ft_error(void);
void		error_in_map(char **split);
void		rev_map(char *map);
void		increase_variables(int *c, int *x);
long int	**get_nbrs_map(char **split, int s_row, int nbr_row, long int **h);
void		put_hexa(char *split_i, int *j, long int *h, int x);
void		get_coordenates_init(long int **m, int s_row, int nbr_row, \
			long int *h);
void		put_final(long int **array, int i);
void		get_horizontal_lines(t_data *img, t_get_coord c);
void		get_vertical_lines(t_data *img, t_get_coord c);
int			get_map_size(long int *array);
void		draw_the_map(t_get_coord c);
void		recalcul_coords_aux(t_get_coord *c, int s_row, int *i, \
			long int **map);
void		put_coords_good(long int **map, t_get_coord c);
int			ft_htoi(char *str, int *b);
#endif
