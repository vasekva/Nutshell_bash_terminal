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

static void	change_curr_path(t_data *shell, int final_num_of_slashs)
{
	int		slash_count;
	char	*new_path;
	int		i;

	i = -1;
	new_path = NULL;
	slash_count = 0;
	while (shell->curr_dir[++i])
	{
		if (final_num_of_slashs == slash_count)
		{
			if (shell->curr_dir[i] == '/')
			{
				new_path = ft_substr(shell->curr_dir, 0, i);
				change_dirs(shell, new_path, "PWD");
				free(new_path);
				chdir(shell->curr_dir);
				break ;
			}
		}
		if (shell->curr_dir[i] == '/')
			slash_count++;
	}
}

static void	cut_path(t_data *shell, int num_of_words, int jump_count)
{
	int	final_num_of_slashs;

	if (num_of_words && jump_count && jump_count > num_of_words)
		jump_count = num_of_words;
	final_num_of_slashs = num_of_words - jump_count;
	if (final_num_of_slashs == 0)
	{
		change_dirs(shell, "/", "PWD");
		chdir(shell->curr_dir);
	}
	else
		change_curr_path(shell, final_num_of_slashs);
}

static void	change_path(t_data *shell, char *old_path, char *des_dir)
{
	int	num_of_words;
	int	jump_count;
	int	i;

	num_of_words = 0;
	jump_count = 0;
	i = -1;
	while (old_path[++i])
		if (old_path[i] == '/' && ft_strlen(old_path) != 1)
			num_of_words++;
	i = -1;
	while (des_dir[++i])
	{
		if (i + 2 <= ft_strlen(des_dir))
		{
			if (des_dir[i] == '.' && des_dir[i + 1] == '.'
				&& des_dir[i + 2] == '/')
			{
				jump_count++;
				i += 2;
			}
		}
	}
	cut_path(shell, num_of_words, jump_count);
}

void	ft_cd_cut_path(t_data *shell, t_cmd *s_cmd)
{
	int		res;

	res = is_file(s_cmd->command[1]);
	if (res == -1)
		exception("cd", s_cmd->command[1], CD_NOTDIR);
	if (res == -2)
		exception("cd", s_cmd->command[1], CD_ACCESS);
	if (res == -3)
		exception("cd", s_cmd->command[1], NO_FILE_OR_DIR);
	change_path(shell, shell->curr_dir, s_cmd->command[1]);
}
