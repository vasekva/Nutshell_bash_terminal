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
	return (0);
}

int	identifier_err(char *command, char *variable)
{
	char	c;

	c = '\'';
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (variable)
	{
		write(2, &c, 1);
		write(2, variable, ft_strlen(variable));
		write(2, &c, 1);
		write(2, ":", 1);
		write(2, " ", 1);
	}
	return (0);
}

static void	print_message(char *command, char *variable)
{
	char	*str_err_code;

	str_err_code = NULL;
	if (command)
	{
		if (!ft_strncmp("$?", command, ft_strlen(command)))
		{
			str_err_code = ft_itoa(g_err_code);
			write(2, str_err_code, ft_strlen(str_err_code));
			free(str_err_code);
		}
		else
			write(2, command, ft_strlen(command));
		write(2, ": ", 2);
	}
	if (variable)
	{
		write(2, variable, ft_strlen(variable));
		write(2, ":", 1);
		write(2, " ", 1);
	}
}

int	command_error(char *command, char *variable)
{
	if (!ft_strncmp("unset", command, ft_strlen(command))
		|| !ft_strncmp("export", command, ft_strlen(command)))
		identifier_err(command, variable);
	else
		print_message(command, variable);
	return (0);
}

int	exception(char *command, char *variable, char *message)
{
	write(2, "minishell: ", 12);
	if (!ft_strncmp(SYNTAX_ERROR, message, ft_strlen(message)))
		syntax_error(variable);
	else
	{
		command_error(command, variable);
		write(2, message, ft_strlen(message));
	}
	write(2, "\n", 1);
	return (deff_err_code(message));
}
