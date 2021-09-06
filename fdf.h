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
	void *mlx;
	void *mlx_win;
}	t_program;

typedef struct s_data
{
	void *img;
	char *ptr;
	int bpp;
	int	line_length;
	int endian;
}	t_data;

typedef struct	s_tools_map
{
	int			fd;
    char		*all_map;
    char		**split;
    int			s_row;
    int     	s_aux;
    int			i;
    int			nbr_row;
    long int	**map;
}	t_tools_map;

typedef struct s_get_coord
{
	int a;
    int b;
    int	x;	//CENTRO
	int y;	//CENTRO
    int x_init;
    int y_init;
    int scale;
    int s_aux;
    int x_aux;
    int c;
    int d;
	int i;
	int j;
    float xinc;
    float yinc;
	long int **array;
}	t_get_coord;

void    ft_error(void);
void rev_hexas(char *map, int *i);
void iso(int *x, int *y, int z);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif