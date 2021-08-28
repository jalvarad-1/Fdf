//#include "fdf.h"
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

int		ft_key(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int main()
{
	t_program	mlx_p;
	t_data		img;

	int	x = 810;	//CENTRO
	int y = 540;	//CENTRO
	double  x_2 = 1010;
	int y_2 = 540;
	int aux;

	mlx_p.mlx = mlx_init();
	mlx_p.mlx_win = mlx_new_window(mlx_p.mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx_p.mlx, 1920, 1080);
	img.ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	y_2 = 0;
	while (y_2 < 201)
	{
			my_pixel_put(&img, x_2, (y_2 + y), 0x0000FF00);
			y_2++;
			aux = (200 * 200) - (y_2 * y_2);
			x_2 = sqrt(aux) + x;
	}
	y_2--;
	aux = (200 * 200) - (y_2 * y_2);
	x_2 = sqrt(aux) + x;
	while (y_2 > -1)
	{
		my_pixel_put(&img, x_2, (y_2 + y), 0x0000FF00);
		y_2--;
		aux = (200 * 200) - (y_2 * y_2);
		x_2 = x - sqrt(aux) ;
	}
	while (y_2 < 201)
	{
		y_2++;
		aux = (200 * 200) - (y_2 * y_2);
		x_2 = x - sqrt(aux);
		my_pixel_put(&img, x_2, (y - y_2), 0x0000FF00);
	}
	while (y_2 > -1)
	{
		y_2--;
		aux = (200 * 200) - (y_2 * y_2);
		x_2 = sqrt(aux) + x;
		my_pixel_put(&img, x_2, (y - y_2), 0x0000FF00);
	}
	mlx_put_image_to_window(mlx_p.mlx, mlx_p.mlx_win, img.img, 0, 0);
	mlx_hook(mlx_p.mlx_win, 2, 3, ft_key, mlx_p.mlx);
	mlx_loop(mlx_p.mlx);
}
