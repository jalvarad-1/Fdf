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

typedef struct	s_values
{
	int		len;
	int		ret;
	int		row;
	int		pos;
	int		fd;
	int		f_amp;
	int		**nbr;
	int		**color;
	int		y;
}	t_values;

typedef struct	s_axis
{
	float		x_0;
	float		x_1;
	float		y_0;
	float		y_1;
}	t_axis;

void    ft_error(void);
#endif