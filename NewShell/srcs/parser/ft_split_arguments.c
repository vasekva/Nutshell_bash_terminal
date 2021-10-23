//
// Created by Achiote Tory on 10/12/21.
//

#include "minishell.h"

void	switcher(char symbol, int *d_q_flag, int *s_q_flag)
{
	if (symbol == '"' && !*s_q_flag)
	{
		if (*d_q_flag)
			*d_q_flag = 0;
		else
			*d_q_flag = 1;
	}
	if (symbol == '\'' && !*d_q_flag)
	{
		if (*s_q_flag)
			*s_q_flag = 0;
		else
			*s_q_flag = 1;
	}
}

static	size_t	ft_count_words_for_args(char const *str, char c)
{
	size_t	i;
	size_t	words;
	int		s_q_flag;
	int		d_q_flag;

	i = -1;
	words = 0;
	s_q_flag = 0;
	d_q_flag = 0;
	while (str[++i])
	{
		if (words == 0 && str[i] != ' ')
			words++;
		switcher(str[i], &d_q_flag, &s_q_flag);
		if (str[i] == c && !d_q_flag && !s_q_flag && \
			str[i + 1] != c && str[i + 1] != '\0')
			words++;
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
	size_t	array_index;
	int		len;
	int		s_q_flag;
	int		d_q_flag;

	array_index = 0;
	s_q_flag = 0;
	d_q_flag = 0;
	while (s[i] != '\0' && array_index < ft_count_words_for_args(s, c))
	{
		len = 0;
		while (s[i] != '\0' && s[i] == c && !s_q_flag && !d_q_flag)
			i++;
		while (s[i + len] != '\0' && (s[i + len] != c || \
		(s[i + len] == c && (s_q_flag || d_q_flag))))
			switcher(s[i + len++], &d_q_flag, &s_q_flag);
		matrix[array_index] = ft_substr(s, i, len);
		if (!matrix[array_index])
		{
			ft_free_words(matrix, array_index);
			return ;
		}
		array_index++;
		i += len;
	}
	matrix[array_index] = NULL;
}

/*
 * split() игнорирующий символ разделения, находящийся внутри кавычек
 */
char	**split_arguments(const char *command, char c)
{
	char	**arguments;
	int		num_words;
	int		i;

	num_words = ft_count_words_for_args(command, c);
	arguments = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!arguments)
		return (NULL);
	i = 0;
	ft_do_words(command, c, i, arguments);
	return (arguments);
}
