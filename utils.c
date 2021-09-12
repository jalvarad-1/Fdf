/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 10:57:58 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 11:15:52 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	del_map(long int **split, int nbr_row)
{
	int	i;

	i = 0;
	while (i < nbr_row)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	del_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	absolute(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	del_str(char *str)
{
	free(str);
	str = NULL;
}

void	increase_variables(int *c, int *x)
{
	(*c)++;
	(*x)++;
}
