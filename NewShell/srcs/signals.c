//
// Created by Achiote Tory on 10/22/21.
//

#include "minishell.h"

void	signal_handler(int signal)
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
