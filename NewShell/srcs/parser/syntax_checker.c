//
// Created by atory on 18.09.2021.
//

#include "minishell.h"

static int	ft_check_redirect(const char *line, int index, char symbol)
{
	while (line[++(index)])
		if (line[index] != ' ')
			break ;
	if (!line[index])
		return (printf("%s `newline'\n", SYNTAX_ERROR));
	if (line[index] == '<' && symbol == '>')
		return (printf("%s `%s'\n", SYNTAX_ERROR, &line[index]));
	if (line[index] == '>' && symbol == '<')
		return (printf("%s `%s'\n", SYNTAX_ERROR, &line[index]));
	return (0);
}

static int	ft_check_pipe(const char *line, int index_forward)
{
	int		index_back;

	index_back = index_forward;
	while (line[--(index_back)])
		if (line[index_back] != ' ')
			break ;
	if (!line[index_back])
		return (printf("%s `|'\n", SYNTAX_ERROR));
	while (line[++(index_forward)])
		if (line[index_forward] != ' ')
			break ;
	if (!line[index_forward])
		return (printf("%s `newline'\n", SYNTAX_ERROR));
	return (0);
}

static int	ft_check_pair(const char *line, int *index, char symbol)
{
	while (line[++(*index)])
		if (line[*index] == symbol)
			break ;
	if (!line[*index])
		return (printf("syntax error : unclosed quote\n"));
	return (0);
}

/**
 * function looks for syntax errors
 * @param line : input command
 * @return	0 : if OK
 * 			any other digit if there is error
 */
int	valid_command(const char *line)
{
	int	index;

	index = -1;
	while (line[++index])
	{
		if (line[index] == ';' || line[index] == '\\')
			return (printf("%s `%c'\n", SYNTAX_ERROR, line[index]));
		if (line[index] == '|')
			if (ft_check_pipe(line, index))
				return (1);
		if (line[index] == '>' || line[index] == '<')
			if (ft_check_redirect(line, index, line[index]))
				return (1);
	}
	index = -1;
	while (line[++index])
		if (line[index] == '"' || line[index] == '\'')
			if (ft_check_pair(line, &index, line[index]))
				return (1);
	return (0);
}
