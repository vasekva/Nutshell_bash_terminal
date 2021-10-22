/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 06:59:51 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 06:59:52 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exception(t_data *shell, char *command, char *variable, char *message)
{
	int	ret;

	if (shell)
	{
		write(2, "minishell: ", 12);
		if (command)
		{
			write(2, command, ft_strlen(command));
			write(2, ": ", 2);
		}
		if (variable)
		{
			write(2, variable, ft_strlen(variable));
			write(2, " ", 1);
		}
	}
	ret = write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	//exit(ret);
}
