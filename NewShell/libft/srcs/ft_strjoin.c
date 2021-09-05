/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:52:47 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:52:49 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fill_s1(char *str, char *s1, int *j, int i)
{
	int	n;

	n = *j;
	i = 0;
	while (s1[i])
	{
		str[n++] = s1[i];
		i++;
	}
	*j = n;
	return (i);
}

void	ft_free(char *s1, char *s2, int flag)
{
	if (flag == -1)
		return ;
	if (flag == 0)
		free(s1);
	if (flag == 1)
		free(s2);
	if (flag == 2)
	{
		free(s1);
		free(s2);
	}
}

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
		i = ft_fill_s1(str, s1, &j, i);
	i = -1;
	if (s2)
	{
		while (s2[++i])
			str[j++] = s2[i];
	}
	str[j] = 0;
	ft_free(s1, s2, flag);
	return (str);
}
