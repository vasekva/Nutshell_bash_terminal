/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:22:01 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:22:05 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_redirect(const char *line, int index, char symbol)
{
	while (line[++(index)])
		if (line[index] != ' ')
			break ;
	if (!line[index])
	{
		exception(SYNTAX_ERROR, "newline", NULL);
		return (1);
	}
	if ((line[index] == '<' && symbol == '>') || \
	(line[index] == '>' && symbol == '<'))
	{
		exception(SYNTAX_ERROR, (char *)&(line[index]), NULL);
		return (1);
	}
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
	{
		exception(SYNTAX_ERROR, "|", NULL);
		return (1);
	}
	while (line[++(index_forward)])
		if (line[index_forward] != ' ')
			break ;
	if (!line[index_forward])
	{
		exception(SYNTAX_ERROR, "newline", NULL);
		return (1);
	}
	return (0);
}

static int	ft_check_pair(const char *line, int *index, char symbol)
{
	while (line[++(*index)])
		if (line[*index] == symbol)
			break ;
	if (!line[*index])
	{
		exception(SYNTAX_ERROR, "unclosed quote", NULL);
		return (1);
	}
	return (0);
}

/**
 * function looks for syntax errors
 * @param line : input command
 * @return	0 : if OK
 * 			any other digit if there is error
 */
int	syntax_check(const char *line)
{
	int		index;
	int		s_q_flag;
	int		d_q_flag;

	index = -1;
	s_q_flag = 0;
	d_q_flag = 0;
	while (line[++index])
	{
		if (line[index] == '"' || line[index] == '\'')
			switcher(line[index], &d_q_flag, &s_q_flag);
		if (line[index] == '|')
			if (ft_check_pipe(line, index))
				return (1);
		if ((line[index] == '>' || line[index] == '<') && \
		!d_q_flag && !s_q_flag)
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
