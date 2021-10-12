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

/*
 * Запускает функцию в которой определяется команда,
 * которую необходимо выполнить
 */
static int	ft_start_shell(t_loginfo *shell)
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
	t_cmd	*ptr;
	t_cmd	*tmp;

	free(line);
	line = NULL;
	ptr = shell->commands;
	while (ptr != NULL)
	{
		arr_free(ptr->command);
		ptr->num_args = 0;
		tmp = ptr;
		ptr = ptr->next;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	shell->commands = NULL;
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
		line = readline(shell.title);
		if (!line)
		{
			write(2, " \b\b exit\n", 9);
			exit(-1);
		}
		if (line[0])
			add_history(line);
		if (!syntax_check(line))
		{
			preparser(&shell, line);
			if (shell.commands && shell.commands->command[0])
				ft_start_shell(&shell);
		}
        ft_free_data(&shell, line);
	}
	return (0);
}
