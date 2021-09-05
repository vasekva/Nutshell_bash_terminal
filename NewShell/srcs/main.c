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
		//rl_replace_line("", 0); TODO: решить проблему с отсутствием функции
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("quit\n");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_loginfo	shell;
	char		*prompt;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_logs(&shell, envp);
	while (1)
	{
		prompt = readline(shell.title);
		if (!prompt)
		{
			write(2, " \b\b exit\n", 9);
			exit(-1);
		}
		if (prompt[0])
			add_history(prompt);
		shell.commands->command = ft_split(prompt, ' ');
		while (shell.commands->command[shell.commands->num_args] != NULL)
			shell.commands->num_args++;
		printf("|||| %d\n", ft_start_shell(shell.commands));
		ft_free_data(shell.commands, prompt);
	}
	return (0);
}

//TODO: объяснить Маше свой strjoin()