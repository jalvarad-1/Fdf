/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:05:49 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/12 11:58:42 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close_win(t_program *i)
{
	mlx_destroy_window(i->mlx, i->mlx_win);
	exit (0);
	return (0);
}

int	ft_key(int keycode)
{
	if (keycode == 53)
	{
		exit(0);
	}
	return (0);
}

void	ft_error(void)
{
	ft_putstr_fd("🚩😥Ups!!!  Something was wrong\n", 1);
	ft_putstr_fd("Please make sure the map has the established format.\n\n", 1);
	ft_putstr_fd("INSTRUCTIONS:\n", 1);
	ft_putstr_fd("- To run this program you have to ", 1);
	ft_putstr_fd("pass the program a single argument,\n", 1);
	ft_putstr_fd("  this argument must be the name of the file ", 1);
	ft_putstr_fd("if it is in the same directory as the program,\n", 1);
	ft_putstr_fd("  or the full path if it is elsewhere.\n\n", 1);
	ft_putstr_fd("- Ensure that your file has the correct rights ", 1);
	ft_putstr_fd("to read the file.\n\n", 1);
	ft_putstr_fd("- Established map format:\n", 1);
	ft_putstr_fd("  You have to pass a map with rectangular form.\n", 1);
	ft_putstr_fd("  All rows must have the same number of numbers(points);", 1);
	ft_putstr_fd("  they cannot be greater than the MAX_INT.\n", 1);
	ft_putstr_fd("  For pass colors to the map your number map has", 1);
	ft_putstr_fd(" to have this format: [number][,][hexadecimal number]\n", 1);
	ft_putstr_fd("  Each row must be separated by a \"\\n\".\n", 1);
	ft_putstr_fd("  Example map:\n\n  0   0,0x00FF00   0\n", 1);
	ft_putstr_fd("  0   0,0x00FF00   1\n  0   0,0x00FF00   1\n\n", 1);
	exit (-1);
}

void	error_in_map(char **split)
{
	del_split(split);
	ft_error();
}
