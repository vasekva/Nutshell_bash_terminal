//
// Created by Achiote Tory on 10/26/21.
//

#include "minishell.h"
/*
 * Запускает функцию в которой определяется команда,
 * которую необходимо выполнить
 */
//static int	ft_start_shell(t_data *shell)
//{
//	if (shell->list_cmds)
//	{
//		if (!deff_curr_cmd(shell))
//			return (0);
//		else
//			return (1);
//	}
//	return (0);
//}

void	ft_start_shell(t_data *shell)
{
	t_cmd	*ptr;

	ptr = shell->list_cmds;
	while (ptr) {
		deff_curr_cmd(shell, ptr);
		if (ptr->is_redirect)
			open_filenames_fd(ptr);
		ptr = ptr->next;
	}
}