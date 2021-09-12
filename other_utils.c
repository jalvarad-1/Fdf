/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:29:05 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:28:01 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_final(long int **array, int i)
{
	array[0][i] = 2147483648;
	array[1][i] = 2147483648;
	array[2][i] = 2147483648;
}

void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_map_size(long int *array)
{
	int	i;
	int	min;
	int	max;

	i = 0;
	min = array[i];
	while (array[i] != 2147483648)
	{
		if (array[i] < min)
			min = array[i];
		i++;
	}
	i = 0;
	max = array[i];
	while (array[i] != 2147483648)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	return (max - min);
}
