/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:03:44 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:03:46 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_minus(t_cmd *s_cmd)
{
	if (arr_get_str_ind(s_cmd, "OLDPWD") == -1)
	{
		printf("OLDPWD not set\n");
		return ;
	}
}

void	cd_with_params(t_cmd *s_cmd)
{
	char	*first_arg;

	first_arg = s_cmd->envp_copy[1];
	if (first_arg[0] == '-')
	{
		cd_minus(s_cmd);
	}
}

int	ft_cd(t_cmd *s_cmd)
{
	char	*tmp_cwd;
	char	*cmd;

	tmp_cwd = NULL;
	cmd = s_cmd->command[1];
	if (s_cmd->num_args == 2 && (char)cmd == '-')
	{
		cd_minus(s_cmd);
		return (0);
	}
	if (!cmd || ft_strncmp(cmd, "--", 2))
	{
		if (arr_get_str_ind(s_cmd, "HOME") < 0)
		{
			return (0);
		}
		else if (arr_get_str_ind(s_cmd, "PWD") < 0)
		{
			tmp_cwd = getcwd(NULL, 0);
			arr_add_var(s_cmd, "PWD", tmp_cwd);
		}
		else
			copy_value(s_cmd, "HOME", "PWD");
	}
	else
	{
		cd_with_params(s_cmd);
	}
	return (0);
}
