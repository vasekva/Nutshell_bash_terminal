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
//		if (variable[0] == '-' && variable[1])
//		{
//			write(2, &variable[0], 2);
//		}
//		else
//		{
			write(2, &c, 1);
			write(2, variable, ft_strlen(variable));
			write(2, &c, 1);
//		}
		write(2, ":", 1);
		write(2, " ", 1);
	}

	return (0);
}

int	command_error(char *command, char *variable)
{
	char *str_err_code;

	str_err_code = NULL;

	if (!ft_strncmp("unset", command, ft_strlen(command))
		|| !ft_strncmp("export", command, ft_strlen(command)))
	{
		identifier_err(command, variable);
	}
	else
	{
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
	return (0);
}

void	deff_err_code(char *message)
{
	int	len;

	len = ft_strlen(message);
	if (!ft_strncmp(EXIT_TOO_MANY_ARGS, message, len) || \
	!ft_strncmp(NO_FILE_OR_DIR, message, len) || \
	!ft_strncmp(CD_NOTDIR, message, len) || \
	!ft_strncmp(INVALID_IDENT, message, len) || \
	!ft_strncmp(EMPTYENV, message, len) || \
	!ft_strncmp(CD_ACCESS, message, len) || \
	!ft_strncmp(CD_NOTDIR, message, len))
		g_err_code = 1;
	if (!ft_strncmp(CMD_NOT_FOUND, message, len))
		g_err_code = 127;
	if (!ft_strncmp(SYNTAX_ERROR, message, len))
		g_err_code = 2;
	if (!ft_strncmp(EXIT_NON_NUMERIC, message, len))
		g_err_code = 255;

}

void	exception(char *command, char *variable, char *message)
{
	write(2, "minishell: ", 12);
//	printf("ERR CODE: %d\n", ERROR_CODE);
	if (!ft_strncmp(SYNTAX_ERROR, message, ft_strlen(message)))
		syntax_error(variable);
	else
	{
		command_error(command, variable);
		write(2, message, ft_strlen(message));
	}
//	deff_err_code(message);
	write(2, "\n", 1);
	deff_err_code(message);
}
