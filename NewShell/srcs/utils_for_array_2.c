/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_array_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:14:01 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:14:04 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_copy(char **array)
{
	char	**tmp_array;
	int		ind;
	int		len;

	ind = 0;
	len = 0;
	tmp_array = NULL;
	while (array[len])
		len++;
	tmp_array = (char **)malloc(sizeof(char *) * (len + 1));
	tmp_array[len] = NULL;
	while (array[ind])
	{
		tmp_array[ind] = ft_strdup(array[ind]);
		ind++;
	}
	return (tmp_array);
}
