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

char	*get_cmd(t_cmd *s_cmd, char *path)
{
	char	*cmd;
	char	*tmp_point;

	cmd = ft_strjoin(path, "/", -1);
	tmp_point = cmd;
	cmd = ft_strjoin(cmd, s_cmd->command[0], -1); //todo: check join
	free(tmp_point);
	return (cmd);
}

int	is_bin_cmd(t_cmd *s_cmd, char *path)
{
	char	*cmd;
	int		status;
	pid_t	pid;
	int		i;

	int ret;
	status = 0;
	i = -1;
	printf("PID IN CMD: %d\n", getpid());

		cmd = get_cmd(s_cmd, path);
		pid = fork();
//		printf("PID: %d\n", getpid());
		if (pid == -1)
			exception(FOUR);
		else if (pid > 0)
		{
			printf("WAITMAIN: %d\n", getpid());
			waitpid(pid, &status, 0);
			free(cmd);
			return (1);
		}
		else
		{
			printf("PID1: %d I: %d\n", getpid(), i);
			ret = execve(cmd, &s_cmd->command[0], s_cmd->envp_copy);
			printf("PID2: %d\n", getpid());
			exit(EXIT_FAILURE);
		}
		printf("GETPID: %d\n", getpid());
		exit(1);
	return (0);
//	}
}

int	deff_curr_cmd(t_loginfo *shell)
{
	char	*cmd;

	cmd = shell->commands->command[0];
	if (is_builtin(cmd))
	{
		if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
			ft_echo(shell->commands);
		if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
			ft_cd(shell->commands);
		if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
			ft_pwd();
		if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
			ft_unset(shell->commands);
		if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
			ft_env(shell->commands);
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			ft_export(shell->commands);
		return (1);
	}
	else
	{
		ft_execve(shell);
	}
}
