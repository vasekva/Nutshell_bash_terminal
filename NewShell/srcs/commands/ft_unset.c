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

void	ft_unset(t_data *shell)
{
	t_env_list *node;
	t_env_list *tmp;
	int		i;

	if (!shell->env_node)
		return ;
	i = 0;
	node = NULL;
	tmp = NULL;
	while (shell->list_cmds->command[++i])
	{
		node = get_node_by_content(shell->env_node, shell->list_cmds->command[i], 0);
		if (!node)
			printf("RETURN NULL\n");
		if (node)
		{
			printf("DEL_VAL: %s\n", node->str);
			if (!shell->env_node->past && !shell->env_node->next)
			{
				printf("ONE ELEM\n");
				free(shell->env_node->key);
				free(shell->env_node->value);
				free(shell->env_node->str);
				free(shell->env_node);
				shell->env_node = NULL;
			}
			else
			{
				if (!node->past)
				{
					if (node->next)
					{
						tmp = shell->env_node;
						shell->env_node = shell->env_node->next;
						shell->env_node->past->next = NULL;
						shell->env_node->past = NULL;
						free_node_content(tmp);
					}
				}
				else if (!node->next)
				{
					printf("DEL LAST\n");
					node->past->next = NULL;
					free_node_content(node);
				}
				else
				{
					printf("DEL MIDDLE\n");
					node->past->next = node->next;
					node->next->past = node->past;
					free_node_content(node);
				}
			}
		}
		if (shell->env_node && shell->env_node->str)
			printf("=====FIRST VAL NOW: %s\n", shell->env_node->str);
		else
			printf("IS EMPTY\n");
	}
}
