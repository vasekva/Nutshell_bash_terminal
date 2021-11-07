/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:41:43 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:21:19 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static void	replace_env_variable(t_env_list *env_node, char **line, \
												int *index, int num_arg)
{
	int		i_start;
	char	*tmp;
	char	nxt_c;

	if (!(*line)[*index + 1])
		return ;
	else
		nxt_c = (*line)[*index + 1];
	if (!ft_isdigit(nxt_c) && !ft_isalpha(nxt_c) && nxt_c != '_' && \
	nxt_c != '?')
		return ;
	tmp = *line;
	i_start = *index;
	if (nxt_c == '?' || ft_isdigit(nxt_c))
	{
		if (nxt_c == '?' && !num_arg)
			return ;
		replace_line_by_nextchar(line, *index, i_start, nxt_c);
	}
	else
		replace_line_by_key(env_node, line, index, i_start);
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
static int	remove_double_quotes(t_env_list *env_node, char **line, \
												int *index, int num_arg)
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
	*index -= 1; //TODO: WWWWTWWTTTFFFFFF two to one and one to two
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

static void	replace_tilda(char *home, char **line, int *index)
{
	int		i_start;
	char	*tmp;

	i_start = *index;
	if (((*line)[i_start + 1] && (*line)[i_start + 1] != ' ' && \
		(*line)[i_start + 1] != '/') || ((*line)[i_start - 1] && \
			(*line)[i_start - 1] != ' '))
		return ;
	tmp = *line;
	*line = ft_replace_dollar(*line, i_start, i_start + 1, home);
	free(tmp);
	*index -= 1;
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
		if (line_ptr[index] == '~')
			replace_tilda(shell->home, &line_ptr, &index);
		if (line_ptr[index] == '$')
			replace_env_variable(shell->env_node, &line_ptr, &index, num_arg);
	}
	return (line_ptr);
}
