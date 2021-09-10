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
	char			*result;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
		return (NULL);
	result = malloc(sizeof(int) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	ft_free(s1, s2, flag);
	return (result);
}
