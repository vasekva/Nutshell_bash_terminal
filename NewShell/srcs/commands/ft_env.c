/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:05:35 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:05:36 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_loginfo *shell)
{
	int	i;

	i = 0;
	while (shell->envp_copy[i])
	{
		printf("%s\n", shell->envp_copy[i]);
		i++;
	}
}
