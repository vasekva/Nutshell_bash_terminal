//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

/**
 * function replaces environment variable with its value in the line
 *
 * @param env_node	:	list of environment variables
 * @param line		:	string to format
 * @param index		:	index of $ sign
 *
 * @return 	returns formatted string
 * @error	calls exception func in case of malloc error
 */
static void	replace_env_variable(t_env_list *env_node, char **line, int *index, int num_arg)
{
	int		i_start;
	char	*key;
	char	*value;
	char	*tmp;

	if (!(*line)[*index + 1] || (*line)[*index + 1] == ' ')
		return ;
	tmp = *line;
	i_start = *index;
	if ((*line)[*index + 1] == '?')
	{
		if (!num_arg)
			return ;
		value = ft_itoa(error_code);
		if (!value)
			exception(NULL, NULL, MALLOC_ERROR);
		*line = ft_replace_dollar(*line, i_start, *index + 2, value);
		free(value);
	}
	else
	{
		while ((*line)[++(*index)])
			if ((*line)[*index] == ' ' || (*line)[*index] == '"' || (*line)[*index] == '\'' || (*line)[*index] == '$' || (*line)[*index] == '?')
				break ;
		key = ft_substr(*line, i_start + 1, *index - i_start - 1);
		if (!key)
			exception(NULL, NULL, MALLOC_ERROR);
		value = get_value_by_key(env_node, key);
		if (value)
			*line = ft_replace_dollar(*line, i_start, *index, value);
		else
			*line = ft_replace_dollar(*line, i_start, *index, "");
		free(key);
	}
	*index = i_start - 1;
	free(tmp);
}

/**
 * function removes double quotes in the line \n
 * replaces environment variables with their values \n
 * if $ sign stands by
 *
 * @param env_node	:	list of environment variables
 * @param line		:	string to format
 * @param index		:	index of quote opening
 *
 * @return	returns 1 if string was formatted\n
 * 			or 0 if quote is unclosed
 * @error	calls exception function if malloc fails
 */
static int	remove_double_quotes(t_env_list *env_node, char **line, int *index, int num_arg)
{
	int		i_start;
	char	*tmp;

	i_start = *index;
	while ((*line)[++(*index)])
	{
		if ((*line)[*index] == '"')
			break ;
		if ((*line)[*index] == '$')
			replace_env_variable(env_node, line, index, num_arg);
	}
	tmp = *line;
	*line = ft_divide_by_quotes(*line, i_start, *index);
	free(tmp);
	*index -= 2;
	return (1);
}

/**
 * function removes single quotes in the line\n
 * other parts of given line are left unchanged
 *
 * @param line :	string to format
 * @param index :	index of quote opening
 *
 * @return	returns 1 if string was formatted \n
 * 			or 0 if quote is unclosed
 * @error	calls exception function if malloc fails
 */
static int	remove_single_quotes(char **line, int *index)
{
	int		i_start;
	char	*tmp;

	i_start = *index;
	while ((*line)[++(*index)])
		if ((*line)[*index] == '\'')
			break ;
	tmp = *line;
	*line = ft_divide_by_quotes(*line, i_start, *index);
	free(tmp);
	*index -= 2;
	return (1);
}

char	*lexer(t_data *shell, char *line, int num_arg)
{
	int		index;
	char	*line_ptr;

	line_ptr = ft_strdup(line);
	if (!line_ptr)
		exception(NULL, NULL, MALLOC_ERROR);
	index = -1;
	while (line_ptr[++index])
	{
		if (line_ptr[index] == '"')
			remove_double_quotes(shell->env_node, &line_ptr, &index, num_arg);
		if (line_ptr[index] == '\'')
			remove_single_quotes(&line_ptr, &index);
		if (line_ptr[index] == '$')
			replace_env_variable(shell->env_node, &line_ptr, &index, num_arg);
	}
	return (line_ptr);
}
