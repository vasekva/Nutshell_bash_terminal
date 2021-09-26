//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

char	*ft_replace_dollar(const char *line, int i_left, int i_right, char *new)
{
	char	*result_line;
	char	*part_line;

	result_line = ft_substr(line, 0, i_left);
	if (!result_line)
		exception("malloc error\n");
	result_line = ft_strjoin(result_line, new, 0);
	if (!result_line)
		exception("malloc error\n");
	part_line = ft_strdup(&line[i_right]);
	if (!part_line)
		exception("malloc error\n");
	result_line = ft_strjoin(result_line, part_line, 0);
	if (!result_line)
		exception("malloc error\n");
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
		exception("malloc error\n");
	result_line = ft_substr(line, i_left + 1, i_right - i_left - 1);
	if (!result_line)
		exception("malloc error\n");
	result_line = ft_strjoin(part_line, result_line, 2);
	if (!result_line)
		exception("malloc error\n");
	part_line = ft_strdup(&line[i_right + 1]);
	if (!part_line)
		exception("malloc error\n");
	result_line = ft_strjoin(result_line, part_line, 2);
	if (!result_line)
		exception("malloc error\n");
	return (result_line);
}
