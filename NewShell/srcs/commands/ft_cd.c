/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:03:44 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:03:46 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *shell)
{
	t_cmd	*s_cmd;

	if (!shell || !shell->list_cmds)
		exception(EMPTYPOINTER);
	s_cmd = shell->list_cmds;
	if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		ft_cd_updir(shell);
	}
	return (0);
}
