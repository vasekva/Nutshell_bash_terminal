#include "minishell.h"

void	ft_exit(t_data *shell)
{
//	printf("exit\n");
    write(2, "exit\n", 5);
	exit(0);
}