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

static void delete_variable_from_list(t_data *shell, t_env_list *del_node)
{
	t_env_list	*tmp;

	tmp = NULL;
	if (!del_node->past && del_node->next)
	{
		tmp = shell->env_node;
		shell->env_node = shell->env_node->next;
		shell->env_node->past->next = NULL;
		shell->env_node->past = NULL;
		free_node_content(tmp);
	}
	else if (!del_node->next)
	{
		del_node->past->next = NULL;
		free_node_content(del_node);
	}
	else
	{
		del_node->past->next = del_node->next;
		del_node->next->past = del_node->past;
		free_node_content(del_node);
	}
}

static void	delete_variable(t_data *shell, t_env_list *del_node)
{
	if (!shell->env_node->past && !shell->env_node->next)
	{
		free(shell->env_node->key);
		free(shell->env_node->value);
		free(shell->env_node->str);
		free(shell->env_node);
		shell->env_node = NULL;
	}
	else
		delete_variable_from_list(shell, del_node);
}

/**
 * Функция проходит по списку полученных значений и, если в
 * переменных окружения есть значение с таким ключом -
 * удаляет переменную из списка путем вызова delete_variable();
 *
 * @param shell:	корневая структура, откуда вытаскиваются значения
 * @param cmd_node:	узел с полученными входными значениями команды
 *
 */
void	ft_unset(t_data *shell, t_cmd *cmd_node)
{
	t_env_list	*del_node;
	int			i;

	if (!shell->env_node || !cmd_node->command[1])
		return ;
	i = 0;
	del_node = NULL;
	while (cmd_node->command[++i])
	{
		if (ft_strlen(cmd_node->command[i]))
		{
			del_node = get_node_by_content(shell->env_node,
					cmd_node->command[i], 0);
			if (del_node && !cmd_node->next && !cmd_node->prev)
				delete_variable(shell, del_node);
			else
			{
				del_node = get_node_by_content(shell->env_node,
						cmd_node->command[i], 1);
				if (del_node && ((cmd_node->prev && i == 1) || !cmd_node->prev))
					exception("unset", del_node->value, UNSET_ERR);
			}
		}
	}
}
