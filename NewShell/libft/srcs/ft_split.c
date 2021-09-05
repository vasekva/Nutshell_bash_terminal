/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:49:47 by jberegon          #+#    #+#             */
/*   Updated: 2020/11/11 22:22:34 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_words(char const *str, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		if (words == 0 && str[i] != c)
			words++;
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
		{
			words++;
		}
		i++;
	}
	return (words);
}

static void	ft_free_words(char **matrix, size_t num)
{
	if (num == 0)
		free(matrix);
	else
	{
		while ((num - 1) > 0)
		{
			free(matrix[num - 1]);
			num--;
		}
		free(matrix);
	}
}

static	void	ft_do_words(const char *s, char c, int i, char **matrix)
{
	size_t		array_index;
	int			len;
	int			start;

	array_index = 0;
	start = 0;
	while (array_index < ft_count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (i == 0 || ((s[i] != c) && (s[i - 1] == c || s[i - 1] == '\0')))
			start = i;
		if (s[i + 1] == c || s[i + 1] == '\0')
		{
			len = i - start + 1;
			matrix[array_index++] = ft_substr(s, i - len + 1, len);
			if (!matrix[array_index - 1])
			{
				ft_free_words(matrix, array_index - 1);
				return ;
			}
		}
		i++;
	}
	matrix[array_index] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**matrix_for_strings;
	int		num_words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	matrix_for_strings = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!matrix_for_strings)
		return (NULL);
	ft_do_words(s, c, i, matrix_for_strings);
	return (matrix_for_strings);
}
