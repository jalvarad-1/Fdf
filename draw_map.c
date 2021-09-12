/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:42:13 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 11:58:36 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	recalcul_coords_aux(t_get_coord *c, int s_row, int *i, long int **map)
{
	while (s_row)
	{
		if (map[c->i][c->j] == 2147483648)
		{
			c->i++;
			c->j = 0;
		}
		c->c = c->x_init;
		c->d = c->y_init;
		iso(&c->c, &c->d, (map[c->i][c->j] * c->scale / 1.5));
		c->array[0][*i] = c->c;
		c->array[1][*i] = c->d;
		(*i)++;
		c->x_init += c->scale;
		s_row--;
		c->j++;
	}
}

void	draw_the_map(t_get_coord c)
{
	t_program	mlx_p;
	t_data		img;
	int			i;

	i = 0;
	mlx_p.mlx = mlx_init();
	mlx_p.mlx_win = mlx_new_window(mlx_p.mlx, 1000, 1000, "fdf");
	img.img = mlx_new_image(mlx_p.mlx, 1000, 1000);
	img.ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	while (c.array[0][i] != 2147483648)
	{
		if (c.array[0][i] < 1000 && c.array[1][i] < 1000)
			my_mlx_pixel_put(&img, c.array[0][i], c.array[1][i], c.array[2][i]);
		i++;
	}
	get_horizontal_lines(&img, c);
	get_vertical_lines(&img, c);
	mlx_put_image_to_window(mlx_p.mlx, mlx_p.mlx_win, img.img, 0, 0);
	mlx_hook(mlx_p.mlx_win, 2, 0, ft_key, mlx_p.mlx);
	mlx_hook(mlx_p.mlx_win, 17, 0, ft_close_win, &mlx_p);
	mlx_loop(mlx_p.mlx);
}
