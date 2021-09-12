/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbrs_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:18:06 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:27:50 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	scroll_next_nbr(char *split_i, int *j)
{
	while (split_i[*j] == '-' || split_i[*j] == '+')
		(*j)++;
	while (split_i[*j] == ' ')
		(*j)++;
	while (ft_isdigit(split_i[*j]))
		(*j)++;
}

static void	init_gnm_ints(int *x, int *i)
{
	*x = 0;
	*i = 0;
}

static void	get_rev_limits_nbrs(long int *map_i, int c, char *split_i, int j)
{
	map_i[c] = ft_atoi(split_i + j);
	if (map_i[c] > INT_MAX || map_i[c] < INT_MIN)
		ft_error();
	if (map_i[c] > 250)
		map_i[c] = 250;
	else if (map_i[c] < -250)
		map_i[c] = -250;
}

static void	reserve_matrix(long int ***map, long int **h, int s_row, int n)
{
	*map = (long int **)malloc(sizeof(long int *) * n);
	*h = malloc(sizeof(long int) * ((n * s_row) + 1));
}

long int	**get_nbrs_map(char **split, int s_row, int n, long int **h)
{
	long int	**map;
	int			i;
	int			j;
	int			c;
	int			x;

	init_gnm_ints(&x, &i);
	reserve_matrix(&map, h, s_row, n);
	while (split[i])
	{
		init_gnm_ints(&j, &c);
		map[i] = malloc(sizeof(long int *) * (s_row + 1));
		while (split[i][j] && c < s_row)
		{
			get_rev_limits_nbrs(map[i], c, split[i], j);
			scroll_next_nbr(split[i], &j);
			put_hexa(split[i], &j, *h, x);
			while (split[i][j] == ' ')
				j++;
			increase_variables(&c, &x);
		}
		map[i][c] = 2147483648;
		i++;
	}
	return (map);
}
