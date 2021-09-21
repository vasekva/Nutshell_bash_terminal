//
// Created by atory on 18.09.2021.
//

#include "minishell.h"

static int	ft_check_redirect(const char *line, int index, char symbol)
{
	while (line[++(index)])
		if (line[index] != ' ')
			break;
	if (!line[index])
		return (printf("syntax error near unexpected token `newline'\n"));
	if (line[index] == '<' && symbol == '>')
		return (printf("syntax error near unexpected token `%s'\n", &line[index]));
	if (line[index] == '>' && symbol == '<')
		return (printf("syntax error near unexpected token `%s'\n", &line[index]));
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
		return (printf("syntax error near unexpected token `|'\n"));
	while (line[++(index_forward)])
		if (line[index_forward] != ' ')
			break ;
	if (!line[index_forward])
		return (printf("syntax error near unexpected token `newline'\n"));
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
	int index;

	index = -1;
	while (line[++index])
	{
		if (line[index] == ';' || line[index] == '\\')
			return (printf("syntax error near unexpected token `%c'\n", line[index]));
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
