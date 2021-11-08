/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:05:38 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/08 12:05:42 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file(char *path)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory != NULL)
	{
		closedir(directory);
		return (1);
	}
	if (errno == ENOTDIR)
		return (-1);
	if (errno == EACCES)
		return (-2);
	return (-3);
}

int	has_file(char *path)
{
	int		res;

	res = is_file(path);
	if (res == -1)
		exception("cd", path, CD_NOTDIR);
	if (res == -2)
		exception("cd", path, CD_ACCESS);
	if (res == -3)
		exception("cd", path, NO_FILE_OR_DIR);
	return (res);
}
