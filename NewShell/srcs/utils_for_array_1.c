/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_array_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:13:00 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:13:01 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_get_str_ind(t_loginfo *shell, char *str)
{
	int	ind;

	ind = 0;
	str = ft_strjoin(str, "=", 3);
	while (shell->envp_copy[ind])
	{
		if (ft_strncmp_old(str, shell->envp_copy[ind], ft_strlen(str)) == 0)
		{
			free(str);
			return (ind);
		}
		ind++;
	}
	free(str);
	return (-1);
}

void	arr_add_var(t_loginfo *shell, char *key, char *value)
{
	int		len;
	char	*tmp_str;

	len = 0;
	tmp_str = ft_strjoin(key, "=", 3);
	tmp_str = ft_strjoin(tmp_str, value, 0);
	while (shell->envp_copy[len])
	{
		len++;
	}
	shell->envp_copy = array_resize(shell->envp_copy, 1);
	shell->envp_copy[len] = ft_strdup(tmp_str);
	free(tmp_str);
}

void	arr_swap_strings(char **array, int first, int second)
{
	char	*first_str;
	char	*second_str;

	first_str = array[first];
	second_str = array[second];
	array[first] = ft_strdup(second_str);
	array[second] = ft_strdup(first_str);
	free(first_str);
	free(second_str);
}

char	**arr_sort(char **array)
{
	int		i;
	int		j;
	char	**sort_array;

	i = 0;
	j = 1;
	sort_array = arr_copy(array);
	while (sort_array[i])
	{
		while (sort_array[j])
		{
			if (ft_strncmp_old(sort_array[j],
					sort_array[i], ft_strlen(sort_array[i])) == -1)
			{
				arr_swap_strings(sort_array, j, i);
			}
			j++;
		}
		j = i + 1;
		i++;
	}
	return (sort_array);
}

void	arr_free(char **array)
{
	int	ind;

	ind = 0;
	if (array != NULL)
	{
		while (array[ind])
		{
			if (array[ind] != NULL)
			{
				free(array[ind]);
				array[ind] = NULL;
			}
			ind++;
		}
		free(array);
		array = NULL;
	}
}
