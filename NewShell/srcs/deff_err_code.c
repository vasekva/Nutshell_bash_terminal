/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deff_err_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:47:10 by atory             #+#    #+#             */
/*   Updated: 2021/11/09 01:47:41 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deff_err_code(char *message)
{
	int	len;

	len = ft_strlen(message);
	if (!ft_strncmp(EXIT_TOO_MANY_ARGS, message, len) || \
	!ft_strncmp(NO_FILE_OR_DIR, message, len) || \
	!ft_strncmp(CD_NOTDIR, message, len) || \
	!ft_strncmp(INVALID_IDENT, message, len) || \
	!ft_strncmp(EMPTYVAR, message, len) || \
	!ft_strncmp(CD_ACCESS, message, len) || \
	!ft_strncmp(CD_NOTDIR, message, len))
		return (1);
	if (!ft_strncmp(CMD_NOT_FOUND, message, len) || \
		!ft_strncmp(EMPTYENV, message, len))
		return (127);
	if (!ft_strncmp(SYNTAX_ERROR, message, len))
		return (2);
	if (!ft_strncmp(EXIT_NON_NUMERIC, message, len))
		return (255);
	return (0);
}
