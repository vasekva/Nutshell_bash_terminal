//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

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
//	char	*tmp;

	i_start = *index;
	while ((*line)[++(*index)]) {
		if ((*line)[*index] == '\'')
			break;
	}
	if (!(*line)[*index])
		return (0);
//	tmp = *line;
	*line = ft_divide_by_quotes(*line, i_start, *index);
//	free(tmp);
	printf("formatted: %s\n", *line);
	return (1);
}

/**
 * function replaces environment variable with its value in the line
 *
 * @param env :		linked list of environment variables
 * @param line :	string to format
 * @param index :	index of $ sign
 *
 * @return 	returns formatted string
 * @error	calls exception func in case of malloc error
 */
static void replace_env_variable(char **envp_copy, char **line, int *index)
{
	int		i_start;
	char	*key;
	char	*value;
	char	*tmp;

	if (!(*line)[*index + 1] || (*line)[*index + 1] == ' ')
		return ;
	i_start = *index;
	while ((*line)[++(*index)])
		if ((*line)[*index] == ' ' || (*line)[*index] == '"' || (*line)[*index] == '\'')
			break ;

	key = ft_substr(*line, i_start + 1, *index - i_start - 1);
	if (!key)
		exception("malloc error\n");
	value = env_get_value_by_key(envp_copy, key);
	tmp = *line;
	if (value)
		*line = ft_replace_dollar(*line, i_start, *index, value);
	else
		*line = ft_replace_dollar(*line, i_start, *index, "");
	free(key);
	free(tmp);
	*index = i_start;
}

char	*lexer(t_loginfo *shell, char *line)
{
	int		index;
	char	*line_ptr;

	line_ptr = line;
	index = -1;
	while (line_ptr[++index])
	{
//		if (line_ptr[index] == ';')
//		{
//			printf("syntax error: ;\n");
//		}
		if (line_ptr[index] == '$')
			replace_env_variable(shell->envp_copy, &line_ptr, &index);
//		if (line_ptr[index] == '"')
//			if (!remove_double_quotes(envp_copy, &line_ptr, &index))
//				error_case("error : unclosed quote\n");
		if (line_ptr[index] == '\'')
			if (!remove_single_quotes(&line, &index))
				exception("error : unclosed quote\n");
	}
	return (line_ptr);
}