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

void	ft_free_data(t_loginfo *shell, char *line)
{
	free(line);
	line = NULL;
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

static void	preparser(t_loginfo shell, char *line)
{
	int		index;
	t_cmd	*ptr;
    char    *line_ptr;

	split_commands(&shell, line);
	ptr = shell.commands;
    while (ptr != NULL)
    {
        index = -1;
        while (ptr->command[++index])
        {
            line_ptr = lexer(&shell, ptr->command[index]);
            free(ptr->command[index]);
            ptr->command[index] = line_ptr;
            printf("%s ", ptr->command[index]);
        }
        printf("\n");
        ptr = ptr->next;
    }
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
		if (valid_command(line))
		{
			free(line);
			continue ;
		}
		preparser(shell, line);
        if (shell.commands && shell.commands->command[0])
            ft_start_shell(&shell);
//        ft_free_data(&shell, line);
	}
	return (0);
}
