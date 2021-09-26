//
// Created by atory on 21.09.2021.
//

#include "minishell.h"

static	size_t	ft_count_words_for_args(char const *str)
{
	size_t	i;
	size_t	words;
	int 	single_quote_flag;
	int 	double_quote_flag;

	i = -1;
	words = 0;
	single_quote_flag = 0;
	double_quote_flag = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!single_quote_flag)
				single_quote_flag = 1;
			else
				single_quote_flag = 0;
		}
		if (words == 0 && str[i] != ' ' && !quote1_flag && !quote2_flag)
			words++;
		if (str[i] == ' ' && str[i + 1] != c && str[i + 1] != '\0')
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

static	void	ft_do_words(const char *s, int i, char **matrix)
{
	size_t		array_index;
	int			len;
	int			start;

	array_index = 0;
	start = 0;
	while (array_index < ft_count_words_for_args(s, c))
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

char **split_arguments(const char *command)
{
	char	**arguments;
	int		num_words;
	int		i;

	num_words = ft_count_words_for_args(command);
	arguments = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!arguments)
		return (NULL);
	ft_do_words(command, i, arguments);
	return (arguments);
}

void split_commands(t_loginfo *shell, char *line)
{
	char 	**commands;
	int		index;
	t_cmd 	*list_ptr;

	commands = ft_split(line, '|');
	if (!commands)
		exception("SPLIT ERROR\n");
	index = -1;
	list_ptr = shell->commands;
	while (commands[++index])
	{
		if (list_ptr)
			list_ptr = list_ptr->next;
		list_ptr = malloc(sizeof(t_cmd));
		if (!list_ptr)
			exception(ONE);
		list_ptr->command = split_arguments(commands[index]);
		if (!list_ptr->command)
			exception(ONE);
		list_ptr->next = NULL;
		printf("%s\n", commands[index]);
	}
}
