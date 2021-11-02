//
// Created by Achiote Tory on 10/22/21.
//

#include "minishell.h"

static void parent_signal_handler(int signal)
{
    if (signal == SIGINT)
	{
        write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
        error_code = 130;
	}
}
void child_signal_handler(int signal)
{
    if (signal == SIGINT) {
        write(2, "\n", 1);
    }
}

void    set_signal_handler(int process_pid)
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
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
        signal(SIGINT, child_signal_handler);
    }
}
