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
		return (0);
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
		return (exception("cd", path, CD_NOTDIR));
	if (res == -2)
		return (exception("cd", path, CD_ACCESS));
	if (res == -3)
		return (exception("cd", path, NO_FILE_OR_DIR));
	return (res);
}

void	ft_putstr_fd(int fd, char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		write(fd, &str[i], 1);
	}
	if (flag)
		write(fd, "\n", 1);
}

int	key_check(char *command, char *variable, int *res)
{
	int		i;
	char	c;

	i = -1;
	while (variable[++i] && variable[i] != '=')
	{
		c = variable[i];
		if (ft_isdigit(c) || (!ft_isalpha(c) && c != '_'))
		{
			*res = exception(command, variable, INVALID_IDENT);
			return (*res);
		}
	}
	return (0);
}
