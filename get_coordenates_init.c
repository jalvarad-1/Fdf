/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordenates_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:24:13 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:26:21 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_the_vectors(t_get_coord *c, int s_row, long int **m, int *i)
{
	while (s_row)
	{
		if (m[c->i][c->j] == 2147483648)
		{
			c->i++;
			c->j = 0;
		}
		c->c = c->x_init;
		c->d = c->y_init;
		iso(&c->c, &c->d, (m[c->i][c->j] * c->scale / 1.5));
		c->array[0][*i] = c->c;
		c->array[1][*i] = c->d;
		(*i)++;
		c->x_init += c->scale;
		s_row--;
		c->j++;
	}
	c->y_init += c->scale;
}

static void	reserve_for_array(t_get_coord *c, int nbr_row, long int *h)
{
	c->array = (long int **)malloc(sizeof(long int *) * 3);
	c->array[0] = malloc(sizeof(long int) * (nbr_row * c->s_aux + 1));
	c->array [1] = malloc(sizeof(long int) *(nbr_row * c->s_aux + 1));
	c->array [2] = h;
	c->i = 0;
}

static long int	**ft_coord_map(int n, long int **m, t_get_coord c, long int *h)
{
	int	i;
	int	s_row;

	i = 0;
	reserve_for_array(&c, n, h);
	while (n)
	{
		s_row = c.s_aux;
		c.x_init = c.x_aux;
		get_the_vectors(&c, s_row, m, &i);
		n--;
	}
	put_final(c.array, i);
	put_coords_good (m, c);
	return (c.array);
}

static void	init_coords(t_get_coord *coords, int s_row, int nbr_row)
{
	coords->x = 500;
	coords->y = 500;
	coords->scale = 50;
	coords->a = (s_row * coords->scale) / 2;
	coords->b = (nbr_row * coords->scale) / 2;
	coords->x_init = coords->x - coords->a;
	coords->y_init = coords->y - coords->b;
	coords->s_aux = s_row;
	coords->x_aux = coords->x_init;
	coords->i = 0;
	coords->j = 0;
}

void	get_coordenates_init(long int **m, int s_row, int nbr_row, long int *h)
{
	t_get_coord	coords;

	init_coords(&coords, s_row, nbr_row);
	coords.array = ft_coord_map (nbr_row, m, coords, h);
	del_map(m, nbr_row);
	coords.a = nbr_row;
	draw_the_map(coords);
}
