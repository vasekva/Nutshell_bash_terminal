/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:22:59 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:23:02 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_err_code = 1;
	}
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_err_code = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		g_err_code = 131;
	}
}

void	set_signal_handler(int process_pid)
{
    rl_catch_signals = 0;
	if (process_pid == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, parent_signal_handler);
	}
	else
	{
		signal(SIGQUIT, child_signal_handler);
		signal(SIGTERM, SIG_DFL);
		signal(SIGINT, child_signal_handler);
	}
}
