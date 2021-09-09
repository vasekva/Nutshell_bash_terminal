/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 06:09:47 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/04 06:09:49 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp_copy(t_loginfo *shell, char *envp[])
{
	int length;

	length = 0;
	while (envp[length])
		length++;
	shell->envp_copy = (char **)malloc(sizeof(char*) * length + 1);
	if (!shell->envp_copy)
		return (0);
	shell->envp_copy[length] = NULL;
	while (--length >= 0)
	{
		shell->envp_copy[length] = ft_strdup(envp[length]);
		if (!shell->envp_copy[length])
			return (0);
	}
	return (1);
}

/*
 * Копирует массив переменных окружения в
 * отдельный двумерный массив для удобства изменения
 */
//static int	ft_copy_env(t_cmd *s_cmd, char **env)
//{
//	int	i;
//
//	i = 0;
//	while (env[i])
//	{
//		i++;
//	}
//	envp_copy = (char **)malloc(sizeof(envp_copy) * i + 1);
//	if (!envp_copy)
//		exception(ONE);
//	i = 0;
//	while (env[i])
//	{
//		envp_copy[i] = ft_strdup(env[i]);
//		if (!envp_copy[i])
//			exception(TWO);
//		i++;
//	}
//	envp_copy[i] = NULL;
//	return (0);
//}

void	init_logs(t_loginfo *shell, char *envp[])
{
	shell->title = ft_strjoin(getenv("LOGNAME"), "/minishell/$> ", -1);
	shell->commands = malloc(sizeof(shell->commands));
	if (!shell->title || !shell->commands)
		exception(ONE);
	shell->envp_copy = NULL;
	get_envp_copy(shell, envp);
//	ft_copy_env(shell->commands, envp);
	shell->commands->command = NULL;
	shell->commands->num_args = 0;
	shell->commands->next = NULL;
}
