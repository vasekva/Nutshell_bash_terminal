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

void	ft_free_data(t_loginfo *shell, char *new_line, char *line)
{
	free(line);
	line = NULL;
	free(new_line);
	new_line = NULL;
	arr_free(shell->commands->command);
	shell->commands->num_args = 0;
	shell->commands->next = NULL;
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
//		printf("atory/minishell/$>   ");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("quit\n");
		exit(1);
	}
}

//int	start_logic(t_loginfo *shell, char *line)
//{
//	shell->commands->command = ft_split(line, ' ');
//	if (!shell->commands->command)
//		printf("SPLIT ERROR \n");
//	while (shell->commands->command[shell->commands->num_args])
//		shell->commands->num_args++;
//	if (shell->commands->command[0])
//		ft_start_shell(shell);
//}

static void	start_logic(t_loginfo *shell, char *line)
{
	int		index;
	t_cmd	*ptr;

//	split_commands(shell, line);
//	ptr = shell->commands;
//	index = -1;
//	while (ptr->command[++index])
}

int	main(int argc, char **argv, char **envp)
{
	t_loginfo	shell;
	char		*line;
	char		*new_line;

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
		if (valid_command(line))
		{
			free(line);
			continue ;
		}
		start_logic(&shell, line);
//		new_line = lexer(&shell, line);
//		start_logic(&shell, new_line);
//		ft_free_data(&shell, new_line, line);

//		start_logic(&shell, line); /* without parsing */
//		ft_free_data(&shell, line);
	}
	return (0);
}
