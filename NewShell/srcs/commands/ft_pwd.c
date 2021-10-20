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

void	ft_pwd(t_data *shell)
{
	//char		*path;
//	t_env_list	*node;
//
//	node = NULL;
//	if (shell->env_node)
//		node = get_node_by_content(shell->env_node, "PWD", 0);
//	if (node)
//	{
//		path = node->value;
//	}
//	else
//		path = getcwd(NULL, 0);
//	if (!path)
//		exit(0);
	printf("%s\n", shell->curr_dir);
	//free(path);
}
