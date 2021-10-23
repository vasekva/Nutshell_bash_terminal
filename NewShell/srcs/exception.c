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

int	syntax_error(char *variable)
{
	write(2, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR));
	write(2, " `", 2);
	write(2, variable, ft_strlen(variable));
	write(2, "\'", 1);
}

void	exception(char *command, char *variable, char *message)
{
	int	ret;

	write(2, "minishell: ", 12);
	if (command == SYNTAX_ERROR)
		syntax_error(variable);
	else
	{
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
