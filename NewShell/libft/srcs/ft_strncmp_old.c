/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:54:08 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:54:09 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_old(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	while (n-- != 0 && (*p_s1 || *p_s2))
	{
		if (*p_s1 < *p_s2)
			return (-1);
		if (*p_s1 > *p_s2)
			return (1);
		p_s1++;
		p_s2++;
	}
	return (0);
}
