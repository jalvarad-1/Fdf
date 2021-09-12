/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines_coords.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:35:15 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:26:41 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_line_in2points2aux(t_data *img, t_get_coord c)
{
	float	x;
	float	y;

	x = c.c;
	y = c.i;
	if (c.i < c.j)
	{
		while (y < c.j)
		{
			x = x + c.xinc;
			y = y + c.yinc;
			my_mlx_pixel_put(img, x, y, c.color);
		}
	}
	else if (c.i > c.j)
	{
		while (y > c.j)
		{
			x = x + c.xinc;
			y = y + c.yinc;
			my_mlx_pixel_put(img, x, y, c.color);
		}
	}
}

static void	get_line_in2points2(t_data *img, t_get_coord c)
{
	int	dx;
	int	dy;
	int	steps;

	dx = c.d - c.c;
	dy = c.j - c.i;
	if (absolute(dx) > absolute(dy))
		steps = absolute(dx);
	else
		steps = absolute(dy);
	c.xinc = dx / (float)steps;
	c.yinc = dy / (float)steps;
	get_line_in2points2aux(img, c);
}

static void	get_line_in2points(t_data *img, t_get_coord c)
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;

	dx = c.d - c.c;
	dy = c.j - c.i;
	if (absolute(dx) > absolute(dy))
		steps = absolute(dx);
	else
		steps = absolute(dy);
	c.xinc = dx / (float)steps;
	c.yinc = dy / (float)steps;
	x = c.c;
	y = c.i;
	while (x < c.d)
	{
		x = x + c.xinc;
		y = y + c.yinc;
		my_mlx_pixel_put(img, x, y, c.color);
	}
}

void	get_vertical_lines(t_data *img, t_get_coord c)
{
	int	i;
	int	n_verticals;
	int	nbr_row;

	nbr_row = c.a;
	n_verticals = 0;
	while (n_verticals < c.s_aux)
	{
		c.b = 0;
		i = n_verticals;
		while (c.array[0][i] != 2147483648 && c.b < (nbr_row - 1))
		{
			c.c = c.array[0][i];
			c.d = c.array[0][i + c.s_aux];
			c.i = c.array[1][i];
			c.j = c.array[1][i + c.s_aux];
			c.color = c.array[2][i];
			get_line_in2points2(img, c);
			i += c.s_aux;
			c.b++;
		}
		n_verticals++;
	}
}

void	get_horizontal_lines(t_data *img, t_get_coord c)
{
	int	i;
	int	nbr_row;
	int	aux_n_row;

	i = 0;
	nbr_row = c.a;
	aux_n_row = 0;
	while (aux_n_row < nbr_row)
	{
		while (c.array[0][i] != 2147483648)
		{
			c.c = c.array[0][i];
			c.d = c.array[0][i + 1];
			c.i = c.array[1][i];
			c.j = c.array[1][i + 1];
			c.color = c.array[2][i];
			get_line_in2points(img, c);
			i++;
			if ((i + 1) % c.s_aux == 0)
			{
				aux_n_row++;
				i++;
			}
		}
	}
}
