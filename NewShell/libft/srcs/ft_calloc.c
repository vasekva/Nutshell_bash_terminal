/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:03:57 by jberegon          #+#    #+#             */
/*   Updated: 2021/10/24 15:03:59 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*p_dest;

	p_dest = destination;
	if (n != 0)
	{
		while (n-- != 0)
			*p_dest++ = (unsigned char)c;
	}
	return (destination);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	size *= count;
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}
