/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_coords_good.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:40:52 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:28:34 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	recalcul_coords(long int **map, t_get_coord c)
{
	int	i;
	int	s_row;

	i = 0;
	c.i = 0;
	c.j = 0;
	while (c.array[0][i] != 2147483648)
	{
		s_row = c.s_aux;
		c.x_init = c.x_aux;
		recalcul_coords_aux(&c, s_row, &i, map);
		c.y_init += c.scale;
	}
}

static void	recalcul_scale(t_get_coord c, int *i, int *j, long int **map)
{
	float	max;

	if (*i >= *j)
		max = *i;
	else
		max = *j;
	c.scale = (c.scale * (980 / max));
	if (c.scale == 0)
		c.scale = 1;
	recalcul_coords (map, c);
}

static int	get_the_center(long int *array, int i)
{
	int	a;
	int	min;

	a = 0;
	min = array[a];
	while (array[a] != 2147483648)
	{
		if (array[a] < min)
			min = array[a];
		a++;
	}
	return (min + i / 2);
}

static void	center_coords(long int **array, int i, int j)
{
	int	x_middle;
	int	y_middle;
	int	x_move;
	int	y_move;
	int	a;

	a = 0;
	x_middle = get_the_center(array[0], i);
	y_middle = get_the_center(array[1], j);
	x_move = 500 - x_middle;
	y_move = 500 - y_middle;
	while (array[0][a] != 2147483648)
	{
		array[0][a] += x_move;
		array[1][a] += y_move;
		a++;
	}
}

void	put_coords_good(long int **map, t_get_coord c)
{
	int	i;
	int	j;

	i = get_map_size(c.array[0]);
	j = get_map_size(c.array[1]);
	recalcul_scale(c, &i, &j, map);
	i = get_map_size(c.array[0]);
	j = get_map_size(c.array[1]);
	center_coords (c.array, i, j);
}
