/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:17:51 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:17:52 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	fr_free_array(t_loginfo *shell)
//{
//	int	i;
//
//	i = -1;
//	while (shell->commands->command[++i] != NULL)
//	{
//		free(shell->commands->command[i]);
//		shell->commands->command[i] = NULL;
//	}
//	free(shell->commands->command);
//	shell->commands->command = NULL;
//}

/*
 * Запускает функцию в которой определяется команда,
 * которую необходимо выполнить
 */
int	ft_start_shell(t_loginfo *shell)
{
	if (shell->commands)
	{
		if (!deff_curr_cmd(shell))
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_free_data(t_loginfo *shell, char *line)
{
	free(line);
	line = NULL;
//	fr_free_array(shell);
	arr_free(shell->commands->command);
	shell->commands->num_args = 0;
	shell->commands->next = NULL;
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\b\b  \n");
		rl_on_new_line();
//		rl_replace_line("", 0); TODO: решить проблему с отсутствием функции
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("quit\n");
		exit(1);
	}
}

int	start_logic(t_loginfo *shell, char *line)
{
	shell->commands->command = ft_split(line, ' ');
	if (!shell->commands->command)
		printf("SPLIT ERROR \n");
	while (shell->commands->command[shell->commands->num_args])
		shell->commands->num_args++;
	if (shell->commands->command[0])
		ft_start_shell(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_loginfo	shell;
	char 		*line;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_logs(&shell, envp);
	while (1)
	{
		line = readline(shell.title);
		if (!line)
		{
			write(2, " \b\b exit\n", 9);
			exit(-1);
		}
		if (line[0])
			add_history(line);
		start_logic(&shell, line);
		ft_free_data(&shell, line);
	}
	return (0);
}
