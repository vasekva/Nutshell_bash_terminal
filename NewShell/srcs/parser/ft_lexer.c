//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

/**
 * function replaces environment variable with its value in the line
 *
 * @param envp_copy	:	array of environment variables
 * @param line		:	string to format
 * @param index		:	index of $ sign
 *
 * @return 	returns formatted string
 * @error	calls exception func in case of malloc error
 */
static void	replace_env_variable(char **envp_copy, char **line, int *index)
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
		*line = ft_replace_dollar(*line, i_start, *index + 2, "CODE OF LAST ERROR HERE");
	else
	{
		while ((*line)[++(*index)])
			if ((*line)[*index] == ' ' || (*line)[*index] == '"' || (*line)[*index] == '\'' || (*line)[*index] == '$')
				break ;
		key = ft_substr(*line, i_start + 1, *index - i_start - 1);
		if (!key)
			exception("malloc error\n");
		value = env_get_value_by_key(envp_copy, key);
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
 * @param envp_copy	:	array of environment variables
 * @param line		:	string to format
 * @param index		:	index of quote opening
 *
 * @return	returns 1 if string was formatted\n
 * 			or 0 if quote is unclosed
 * @error	calls exception function if malloc fails
 */
static int	remove_double_quotes(char **envp_copy, char **line, int *index)
{
	int		i_start;
	char	*tmp;

	i_start = *index;
	while ((*line)[++(*index)])
	{
		if ((*line)[*index] == '"')
			break ;
		if ((*line)[*index] == '$')
			replace_env_variable(envp_copy, line, index);
	}
	tmp = *line;
	*line = ft_divide_by_quotes(*line, i_start, *index);
	free(tmp);
	*index -= 1;
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

char	*lexer(t_loginfo *shell, char *line)
{
	int		index;
	char	*line_ptr;

	line_ptr = ft_strdup(line);
	if (!line_ptr)
		exception("malloc error\n");
	index = -1;
	while (line_ptr[++index])
	{
		if (line_ptr[index] == '"')
			remove_double_quotes(shell->envp_copy, &line_ptr, &index);
		if (line_ptr[index] == '\'')
			remove_single_quotes(&line_ptr, &index);
		if (line_ptr[index] == '$')
			replace_env_variable(shell->envp_copy, &line_ptr, &index);
	}
	return (line_ptr);
}
