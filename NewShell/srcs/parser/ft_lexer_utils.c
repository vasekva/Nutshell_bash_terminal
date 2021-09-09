//
// Created by Achiote Tory on 9/9/21.
//

#include "minishell.h"

char	*ft_dollar_replacer(const char *line, int i_left, int i_right, char *part_to_replace)
{
	char	*tmp_ptr;
	char 	*result_line;
	char 	*part_line;

	part_line = ft_substr(line, 0, i_left);
	if (!part_line)
		exception("malloc error\n");

//	tmp_ptr = result_line;
//	free inside:
	result_line = ft_strjoin(part_line, part_to_replace, -1);
	if (!result_line)
		exception("malloc error\n");

//	free(tmp_ptr);
//	free(part_line);

	part_line = ft_strdup(&line[i_right]);
	if (!part_line)
		exception("malloc error\n");

//	tmp_ptr = result_line;
//	free inside:
	result_line = ft_strjoin(result_line, part_line, -1);
	if (!result_line)
		exception("malloc error\n");
//	free(tmp_ptr);
	return (result_line);
}