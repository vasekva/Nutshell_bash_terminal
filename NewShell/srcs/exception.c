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

void	exception(char *message)
{
	int	ret;

	ret = write(2, message, ft_strlen(message));
	write(1, "\n", 1);
	exit(ret);
}
