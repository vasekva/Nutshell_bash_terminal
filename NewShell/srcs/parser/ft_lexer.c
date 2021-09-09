//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

/**
 * function replaces environment variable with its value in the line
 *
 * @param env :		linked list of environment variables
 * @param line :	string to format
 * @param index :	index of $ sign
 *
 * @return 	returns formatted string
 * @error	calls error func if variable is not found \n
 * 			in case of malloc error \n
 * 			if there is no such environment variable in list
 */
static int replace_env_variable(char **env, char **line, int *index)
{
	int		i_start;
	char	*tmp_ptr;
	char	*key;
	char	*value;
	char	*result_line;

	if (!(*line)[*index + 1] || (*line)[*index + 1] == ' ')
		return (1);
	i_start = *index;
	while ((*line)[++(*index)])
		if ((*line)[*index] == ' ' || (*line)[*index] == '"' || (*line)[*index] == '\'') /* todo: ' & "*/
			break ;

	key = ft_substr(*line, i_start + 1, *index - i_start - 1);
	if (!key)
		exception("malloc error\n");
	printf("  //		key: %s\n", key);

	value = env_get_value_by_key(env, key);
	printf("  //		value: %s\n", value);

	*line = ft_dollar_replacer(*line, i_start, *index, value);
	printf("  // result: %s\n\n", *line);
	return (1);
}

char	*lexer(t_loginfo *shell, char *line)
{
	int		index;
	char	*line_ptr;

//	printf("\n  // raw: %s\n", line);
	line_ptr = line;
	index = -1;
	while (line_ptr[++index])

	{
		if (line_ptr[index] == '$')
		{
			replace_env_variable(shell->envp_copy, &line_ptr, &index);
		}
//		if (line_ptr[index] == '"')
//			if (!remove_double_quotes(envp_copy, &line_ptr, &index))
//				error_case("error : unclosed quote\n");
//		if (line_ptr[index] == '\'')
//			if (!remove_single_quotes(&line, &index))
//				error_case("error : unclosed quote\n");
	}
//	free(line); free inside ft_free_data
	return (line_ptr);
}