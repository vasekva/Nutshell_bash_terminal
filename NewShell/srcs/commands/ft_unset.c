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

void	ft_unset(t_cmd *s_cmd)
{
	int		i;
	int		ind;
	char	*tmp_str;

	i = 1;
	ind = 0;
	tmp_str = NULL;
	while (s_cmd->command[i])
	{
		ind = arr_get_str_ind(s_cmd, s_cmd->command[i]);
		if (ind >= 0)
		{
			tmp_str = s_cmd->envp_copy[ind];
			s_cmd->envp_copy[ind] = ft_strdup("\0");
			free(tmp_str);
		}
		i++;
	}
	s_cmd->envp_copy = array_resize(s_cmd->envp_copy, -1);
}
