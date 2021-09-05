/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:52:57 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:52:58 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == 0)
	{
		while (*s)
		{
			s++;
		}
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}
