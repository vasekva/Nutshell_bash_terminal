/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:21:04 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:21:10 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_dollar(const char *line, int i_left, int i_right, char *new)
{
	char	*result_line;
	char	*part_line;

	result_line = ft_substr(line, 0, i_left);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	result_line = ft_strjoin(result_line, new, 0);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	part_line = ft_strdup(&line[i_right]);
	if (!part_line)
		exception(NULL, NULL, MALLOC_ERROR);
	result_line = ft_strjoin(result_line, part_line, 0);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	free(part_line);
	return (result_line);
}

/**
 * function splits string by given indexes \n
 * joins parts into one line without dividers
 *
 * @param line :	string to format
 * @param i_left :	index of first divider
 * @param i_right : index of second divider
 *
 * @return	returns formatted string
 * @error	calls exception function in case of malloc error
 */
char	*ft_divide_by_quotes(const char *line, int i_left, int i_right)
{
	char	*result_line;
	char	*part_line;

	part_line = ft_substr(line, 0, i_left);
	if (!part_line)
		exception(NULL, NULL, MALLOC_ERROR);
	result_line = ft_substr(line, i_left + 1, i_right - i_left - 1);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	result_line = ft_strjoin(part_line, result_line, 2);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	part_line = ft_strdup(&line[i_right + 1]);
	if (!part_line)
		exception(NULL, NULL, MALLOC_ERROR);
	result_line = ft_strjoin(result_line, part_line, 2);
	if (!result_line)
		exception(NULL, NULL, MALLOC_ERROR);
	return (result_line);
}

void	replace_line_by_key(t_env_list *env_node, char **line, \
										int *index, int i_start)
{
	char	*key;
	char	*value;

	while ((*line)[++(*index)])
		if (!ft_isdigit((*line)[*index]) && !ft_isalpha((*line)[*index]) && \
		(*line)[*index] != '_')
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

void	replace_line_by_nextchar(char **line, int index, int i_start, \
															char nxt_c)
{
	char	*value;

	if (nxt_c == '?')
		value = ft_itoa(g_err_code);
	else
		value = ft_strdup("");
	if (!value)
		exception(NULL, NULL, MALLOC_ERROR);
	*line = ft_replace_dollar(*line, i_start, index + 2, value);
	free(value);
}
