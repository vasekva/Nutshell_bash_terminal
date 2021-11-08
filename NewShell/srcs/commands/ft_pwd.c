/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:08:31 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:08:33 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(node->fd_output, path, 1);
	free(path);
	return (0);
}
