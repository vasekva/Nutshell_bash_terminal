/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:08:51 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:08:52 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data *shell)
{
	int		i;
	int		ind;
	char	*tmp_str;
	t_cmd	*s_cmd;

	i = 1;
	ind = 0;
	tmp_str = NULL;
	s_cmd = shell->list_cmds;
	while (s_cmd->command[i])
	{
		ind = arr_get_str_ind(shell, s_cmd->command[i]);
		if (ind >= 0)
		{
			tmp_str = shell->envp_copy[ind];
			shell->envp_copy[ind] = ft_strdup("\0");
			free(tmp_str);
		}
		i++;
	}
	shell->envp_copy = array_resize(shell->envp_copy, -1);
}
