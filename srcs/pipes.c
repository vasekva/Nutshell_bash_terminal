/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:22:21 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:22:29 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_shell(t_data *shell)
{
	t_cmd	*ptr;

	ptr = shell->list_cmds;
	while (ptr)
	{
		if (ptr->is_redirect)
			open_filenames_fd(ptr);
		deff_curr_cmd(shell, ptr);
		ptr = ptr->next;
	}
}
