/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deff_curr_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:59:39 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:59:40 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char	*cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0
	)
	{
		return (1);
	}
	else
		return (0);
}

int	deff_curr_cmd(t_data *shell, t_cmd *node)
{
	char	*cmd;

	cmd = node->command[0];
	if (is_builtin(cmd))
	{
		if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
			ft_echo(node);
		if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
			ft_cd(shell, node);
		if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
			ft_pwd(node);
		if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
			ft_unset(shell, node);
		if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
			ft_env(shell, node);
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			ft_export(shell, node);
		if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
			ft_exit(shell, node);
		return (1);
	}
	else
		ft_execve(shell, node);
	return (0);
}
