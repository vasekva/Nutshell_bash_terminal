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

int	is_builtin(char	*cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0
	)
	{
		return (1);
	}
	else
		return (0);
}

int	is_bin_cmd(t_cmd *s_cmd)
{
	char	**paths;
	char	*tmp_str;
	char	*try_cmd;

	tmp_str = env_get_value_by_key(s_cmd->envp_copy, "PATH");
	paths = ft_split(tmp_str, ':'); //TODO: проверка ft_split()

	int i = -1;
	while (paths[++i])
	{
		try_cmd = ft_strjoin(paths[i], "/", -1);
		try_cmd = ft_strjoin(try_cmd, s_cmd->command[0], -1);

		if (execve(try_cmd, &s_cmd->command[0], s_cmd->envp_copy) != -1)
			return (1);
//			printf("%s\n", try_cmd);
	}
	//TODO: free array
	//TODO: разобраться почему программа закрывается при успешном execve()
	return (0);
}

int	deff_curr_cmd(t_cmd *s_cmd)
{
	char	*cmd;

	cmd = s_cmd->command[0];
	if (is_builtin(cmd))
	{
		if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
			ft_echo(s_cmd);
		if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
			ft_cd(s_cmd);
		if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
			ft_pwd();
		if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
			ft_unset(s_cmd);
		if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
			ft_env(s_cmd);
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			ft_export(s_cmd);
		return (1);
	}
	else
	{
//		if (is_bin_cmd(s_cmd))
//			return (1); //todo: sega tut
		printf("%s: command not found\n", cmd);
		return (0);
	}
}
