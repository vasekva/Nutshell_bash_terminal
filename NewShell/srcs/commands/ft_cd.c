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

void	cd_minus(t_data *shell)
{
	if (arr_get_str_ind(shell, "OLDPWD") == -1)
	{
		printf("OLDPWD not set\n");
		return ;
	}
}

void	cd_with_params(t_data *shell)
{
	char	*first_arg;

	first_arg = shell->envp_copy[1];
	if (first_arg[0] == '-')
	{
		cd_minus(shell);
	}
}

int	ft_cd(t_data *shell)
{
	char	*tmp_cwd;
	char	*cmd;
	t_cmd	*s_cmd;

	tmp_cwd = NULL;
	s_cmd = shell->list_cmds;
	cmd = s_cmd->command[1];
	if (s_cmd->num_args == 2 && cmd[0] == '-')
	{
		cd_minus(shell);
		return (0);
	}
	if (!cmd || ft_strncmp(cmd, "--", 2))
	{
		if (arr_get_str_ind(shell, "HOME") < 0)
		{
			return (0);
		}
		else if (arr_get_str_ind(shell, "PWD") < 0)
		{
			tmp_cwd = getcwd(NULL, 0);
			arr_add_var(shell, "PWD", tmp_cwd);
		}
		else
			copy_value(shell, "HOME", "PWD");
	}
	else
	{
		cd_with_params(shell);
	}
	return (0);
}
