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
        error_code = 1;
	}
}
void child_signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(2, "\n", 1);
        error_code = 130;
    }
    else if (signal == SIGQUIT)
    {
    	write(2, "Quit: 3\n", 8);
    	error_code = 131;
    }
}

void    set_signal_handler(int process_pid)
{
//    rl_catch_signals = 0; //TODO: желательно чтоб это было раскоментчено
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
