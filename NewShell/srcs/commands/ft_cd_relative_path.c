/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_parse_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:56:20 by jberegon          #+#    #+#             */
/*   Updated: 2021/10/24 16:56:27 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_path(char *path, int flag)
{
	char	*new_path;
	int		len;

	len = ft_strlen(path);
	if (len == 1)
		return (path);
	new_path = NULL;
	if (flag == -1)
	{
		while (path[len] != '/')
		{
			if (len == 1)
				break ;
			len--;
		}
		new_path = ft_substr(path, 0, len);
		free(path);
	}
	return (new_path);
}

void	change_path(int *i, int *left_pos, char **des_dir, char **new_path)
{
	char	*cut;

	*left_pos = *i;
	while ((*des_dir)[*i] != '\0' && (*des_dir)[*i] && (*des_dir)[*i] != '/')
		(*i)++;
	cut = ft_substr(*des_dir, *left_pos, (*i) - (*left_pos));
	if ((*new_path)[ft_strlen(*new_path) - 1] != '/')
		cut = ft_strjoin("/", cut, 1);
	*new_path = ft_strjoin(*new_path, cut, 2);
}

void	new_change_path(t_data *shell, t_cmd *s_cmd,
		char *old_path, char *des_dir)
{
	int		i;
	int		left_pos;
	char	*new_path;

	i = -1;
	left_pos = 0;
	new_path = ft_strdup(old_path);
	while (des_dir[++i])
	{
		if ((i + 2) <= ft_strlen(des_dir) && (des_dir[i] == '.'
				&& des_dir[i + 1] == '.' && des_dir[i + 2] == '/'))
		{
			new_path = cut_path(new_path, -1);
			i += 2;
			left_pos = i;
		}
		if (des_dir[i] != '.' && des_dir[i] != '/')
		{
			change_path(&i, &left_pos, &des_dir, &new_path);
		}
	}
	change_dirs(shell, new_path, "PWD");
	free(new_path);
}

void	relative_path(t_data *shell, t_cmd *s_cmd)
{
	int		res;

	res = has_file(s_cmd->command[1]);
	if (res == 1)
		new_change_path(shell, s_cmd, shell->curr_dir, s_cmd->command[1]);
}
