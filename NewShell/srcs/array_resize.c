/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_resize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:57:59 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:58:01 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**remove_empty_cells(char **src)
{
	char	**tmp_array;
	int		len;
	int		ind;

	len = -1;
	ind = 0;
	while (src[++len])
	{
		if (ft_strncmp(src[len], "\0", ft_strlen(src[len])) == 0)
			ind++;
	}
	len -= ind;
	tmp_array = (char **)malloc(sizeof(char **) * (len + 1));
	tmp_array[len] = NULL;
	len = -1;
	ind = -1;
	while (src[++len])
	{
		if (ft_strncmp(src[len], "\0", ft_strlen(src[len])) != 0)
		{
			tmp_array[++ind] = ft_strdup(src[len]);
		}
	}
	return (tmp_array);
}

static char	**add_empty_cell(char **src)
{
	char	**tmp_array;
	int		len;
	int		ind;

	len = 0;
	ind = 0;
	while (src[len])
		len++;
	tmp_array = (char **)malloc(sizeof(*tmp_array) * (len + 1));
	while (src[ind])
	{
		tmp_array[ind] = ft_strdup(src[ind]);
		ind++;
	}
	tmp_array[ind] = "\0";
	tmp_array[ind + 1] = NULL;
	return (tmp_array);
}

char	**array_resize(char **src, int flag)
{
	char	**tmp_arr;

	tmp_arr = NULL;
	if (flag > 0)
		tmp_arr = add_empty_cell(src);
	if (flag < 0)
		tmp_arr = remove_empty_cells(src);
	arr_free(src);
	return (tmp_arr);
}
