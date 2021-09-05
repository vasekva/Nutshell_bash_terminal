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

void	fr_free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

/*
 * Запускает функцию в которой определяется команда,
 * которую необходимо выполнить
 */
int	ft_start_shell(t_cmd *s_cmd)
{
	if (s_cmd)
	{
		if (!deff_curr_cmd(s_cmd))
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_free_data(t_cmd	*s_cmd, char *str)
{
	fr_free_array(s_cmd->command);
	free(str);
	s_cmd->num_args = 0;
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
	line = readline(shell->title);
	if (!line)
	{
		write(2, " \b\b exit\n", 9);
		exit(-1);
	}
	if (line[0])
		add_history(line);
	shell->commands->command = ft_split(line, ' ');
	if (!shell->commands->command)
		printf("SPLIT ERROR \n");
	while (shell->commands->command[shell->commands->num_args])
		shell->commands->num_args++;
	if (shell->commands->command[0])
		ft_start_shell(shell->commands);
	ft_free_data(shell->commands, line);
}

int	main(int argc, char **argv, char **envp)
{
	t_loginfo	shell;
	char		*line;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_logs(&shell, envp);
	while (1)
	{
		start_logic(&shell, line);
//		line = readline(shell.title);
//		if (!line)
//		{
//			write(2, " \b\b exit\n", 9);
//			exit(-1);
//		}
//		if (line[0])
//			add_history(line);
//		shell.commands->command = ft_split(line, ' ');
//		if (!shell.commands->command)
//			printf("SPLIT ERROR \n");
//
//		printf("|%s|\n", &shell.commands->command[0]);
//		while (shell.commands->command[shell.commands->num_args])
//			shell.commands->num_args++;
//		printf("|%s|\n", &shell.commands->command[0]);
//
//		ft_start_shell(shell.commands);
//		printf("|%s|\n", &shell.commands->command[0]);
//		printf("|%s|\n", &shell.commands->command[1]);
//		ft_free_data(shell.commands, line);
	}
	return (0);
}

//TODO: объяснить Маше свой strjoin()