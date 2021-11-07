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

static void add_path(t_data *shell, t_cmd *s_cmd)
{
	char	*new_path;

	new_path = ft_strjoin(shell->curr_dir,
		ft_strjoin("/", s_cmd->command[1], -1), 1);
//	new_path = ft_strjoin(shell->curr_dir,s_cmd->command[1], -1);
	change_dirs(shell, new_path, "PWD");
	free(new_path);
}

static void	cut_path(t_data *shell, t_cmd *s_cmd, int num_of_words, int jump_count)
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
	{
		if (jump_count == 0)
			add_path(shell, s_cmd);
		else
			change_curr_path(shell, final_num_of_slashs);
	}
}

//static void	change_path(t_data *shell, t_cmd *s_cmd, char *old_path, char *des_dir)
//{
//	int	num_of_words;
//	int	jump_count;
//	int	i;
//
//	num_of_words = 0;
//	jump_count = 0;
//	i = -1;
//	while (old_path[++i])
//		if (old_path[i] == '/' && ft_strlen(old_path) != 1)
//			num_of_words++;
//	i = -1;
//	while (des_dir[++i])
//	{
//		if (i + 2 <= ft_strlen(des_dir))
//		{
//			if (des_dir[i] == '.' && des_dir[i + 1] == '.'
//				&& des_dir[i + 2] == '/')
//			{
//				jump_count++;
//				i += 2;
//			}
//		}
//	}
//	cut_path(shell, s_cmd, num_of_words, jump_count);
//	printf("NUM: %d JUMP: %d\n", num_of_words, jump_count);
//}


char	*change_path(char *path, int flag)
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
			{
				break;
			}
			len--;
		}
		new_path = ft_substr(path, 0, len);
		free(path);
//		printf("new path: %s\n", new_path);
	}
	return (new_path);
}

void	new_change_path(t_data *shell, t_cmd *s_cmd, char *old_path, char *des_dir)
{
	int	i;
	int len;
	int	left_pos;
	char	*new_path;
	char	*tmp_str;

	i = -1;
	left_pos = 0;
	len = ft_strlen(des_dir);
	new_path = ft_strdup(old_path);
	tmp_str = des_dir;
	while (tmp_str[++i])
	{
		if ((i + 2) <= len)
		{
			if (tmp_str[i] == '.' && tmp_str[i + 1] == '.'
				&& tmp_str[i + 2] == '/')
			{
				new_path = change_path(new_path, -1);
				i += 2;
				left_pos = i;
			}
		}
		if (tmp_str[i + 1] && tmp_str[i] != '.' && tmp_str[i] != '/')
		{
			left_pos = i;
			while (tmp_str[i] != '\0' && tmp_str[i] && tmp_str[i] != '/')
				i++;
			char *cut = ft_substr(des_dir, left_pos, i - left_pos);
//			if (ft_strlen(shell->curr_dir) != 1)
//				cut = ft_strjoin("/", cut, 1);
//			printf("cUT: %s\n", cut);
			if (ft_strlen(new_path) != 1)
				cut = ft_strjoin("/", cut, 1);
			new_path = ft_strjoin(new_path, cut, 2);
//			printf("New path: %s\n", new_path);
		}

	}
//	printf("|%s|\n", new_path);
//	printf("RELATIVE\n");
	change_dirs(shell, new_path, "PWD");
	free(new_path);
}

void	relative_path(t_data *shell, t_cmd *s_cmd)
{
	int		res;

//	printf("RELATIVE\n");
//	printf("|%s|\n", shell->curr_dir);
	res = has_file(s_cmd->command[1]);
//	if (res == 1)
//		change_path(shell, s_cmd, shell->curr_dir, s_cmd->command[1]);
	if (res == 1)
		new_change_path(shell, s_cmd, shell->curr_dir, s_cmd->command[1]);
}
