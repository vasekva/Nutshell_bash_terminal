//
// Created by atory on 21.09.2021.
//

#include "minishell.h"

static	size_t	ft_count_words_for_args(char const *str, char c)
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
		if (words == 0 && str[i] != ' ')
			words++;
		if (str[i] == '"' && !single_quote_flag)
		{
			if (double_quote_flag)
				double_quote_flag = 0;
			else
				double_quote_flag= 1;
		}
		if (str[i] == '\'' && !double_quote_flag)
		{
			if (single_quote_flag)
				single_quote_flag = 0;
			else
				single_quote_flag = 1;
		}
		if (str[i] == c && !double_quote_flag && !single_quote_flag && str[i + 1] != c && str[i + 1] != '\0')
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
	int		start;
	int 	single_quote_flag;
	int 	double_quote_flag;

	array_index = 0;
	start = 0;
	single_quote_flag = 0;
	double_quote_flag = 0;
	while (array_index < ft_count_words_for_args(s, c))
	{
		if (s[i] == '"' && !single_quote_flag)
		{
			if (double_quote_flag)
				double_quote_flag = 0;
			else
				double_quote_flag= 1;
		}
		if (s[i] == '\'' && !double_quote_flag)
		{
			if (single_quote_flag)
				single_quote_flag = 0;
			else
				single_quote_flag = 1;
		}
		while (s[i] && s[i] == c && !double_quote_flag && !single_quote_flag)
			i++;
		if (i == 0 || ((s[i] != c) && !single_quote_flag && !double_quote_flag && (s[i - 1] == c || s[i - 1] == '\0')))
			start = i;
		if (!double_quote_flag && !single_quote_flag && (s[i + 1] == c || s[i + 1] == '\0'))
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

char	**split_arguments(const char *command, char c)
{
	char	**arguments;
	int		num_words;
	int		i;

	num_words = ft_count_words_for_args(command, c);
	printf("NUM : %d\n", num_words);
	arguments = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!arguments)
		return (NULL);
	i = 0;
	ft_do_words(command, c, i, arguments);
	i = -1;
	while (arguments[++i])
		printf("%s\n", arguments[i]);
	return (arguments);
}




//
//
//
//


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
		list_ptr->command = split_arguments(commands[index], ' ');
		if (!list_ptr->command)
			exception(ONE);
		//todo : посчитать
		printf("STOP\n\n");
		list_ptr->next = NULL;
		printf("%s\n", commands[index]);
	}
}
