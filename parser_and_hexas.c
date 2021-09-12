/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_hexas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:13:41 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 12:28:15 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rev_hexas(char *map, int *i)
{
	int	b;

	b = 0;
	if (map[*i] != '0' || map[(*i) + 1] != 'x')
		ft_error();
	(*i) += 2;
	while (map[*i] && (map[*i] != ' ' && map[*i] != '\n'))
	{
		if (map[*i] < '0' || (map[*i] > '9' && map[*i] < 'A'))
			ft_error();
		if ((map[*i] > 'F' && map[*i] < 'a') || map[*i] > 'f')
			ft_error();
		(*i)++;
		b++;
	}
	if (b > 6)
		ft_error ();
}

void	rev_map(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		while (map[i] == ' ')
			i++;
		if (map[i] == '-' || map[i] == '+')
			i++;
		if (!ft_isdigit(map[i]))
			ft_error();
		while (ft_isdigit(map[i]))
			i++;
		if (map [i] == ',')
		{
			i++;
			rev_hexas(map, &i);
		}
		if (map[i] != '\0' && map[i] != ' ' && map[i] != '\n')
			ft_error ();
		while (map[i] == ' ')
			i++;
		while (map [i] == '\n')
			i++;
	}
}

void	put_hexa(char *split_i, int *j, long int *h, int x)
{
	if (split_i[*j] == ',')
	{
		(*j)++;
		h[x] = ft_htoi(split_i, j);
	}
	else
		h[x] = 0xFFFFFF;
}

int	ft_htoi(char *str, int *b)
{
	int	len;
	int	dec;
	int	base;

	(*b) += 2;
	while (str[*b] && str[*b] != ' ' && str[*b] != '\n')
		(*b)++;
	len = (*b) - 1;
	dec = 0;
	base = 1;
	while (str[len] != 'x' && str[len] != 'X')
	{
		if (ft_isdigit(str[len]))
			dec += (str[len] - 48) * base;
		else if (str[len] >= 'A' && str[len] <= 'F')
			dec += (str[len] - 55) * base;
		else if (str[len] >= 'a' && str[len] <= 'f')
			dec += (str[len] - 87) * base;
		base *= 16;
		len--;
	}
	return (dec);
}
