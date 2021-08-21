/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:02:14 by jalvarad          #+#    #+#             */
/*   Updated: 2021/08/15 16:02:23 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	ts;
	size_t	td;

	ts = ft_strlen(src);
	td = ft_strlen(dst);
	a = 0;
	if (dstsize == 0)
		return (ts);
	if (dstsize < td)
		return (ts + dstsize);
	while (src[a] && (td + a) < dstsize - 1)
	{
		dst[td + a] = src[a];
		a++;
	}
	dst[td + a] = 0;
	return (ts + td);
}
