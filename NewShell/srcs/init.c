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

static void	get_envp_copy(t_loginfo *shell, char *envp[])
{
	int length;

	length = 0;
	while (envp[length])
		length++;
	shell->envp_copy = (char **)malloc(sizeof(char*) * length + 1);
	if (!shell->envp_copy)
		exception(ONE);
	shell->envp_copy[length] = NULL;
	while (--length >= 0)
	{
		shell->envp_copy[length] = ft_strdup(envp[length]);
		if (!shell->envp_copy[length])
			exception(ONE);
	}
}

void	init_logs(t_loginfo *shell, char *envp[])
{
	shell->title = ft_strjoin(getenv("LOGNAME"), "/minishell/$> ", -1);
//	shell->commands = malloc(sizeof(shell->commands));
//	if (!shell->title || !shell->commands)
//		exception(ONE);
	if (!shell->title)
		exception(ONE);
	shell->envp_copy = NULL;
	get_envp_copy(shell, envp);

	shell->commands = NULL;
//	shell->commands->command = NULL;
//	shell->commands->num_args = 0;
//	shell->commands->next = NULL;
}
