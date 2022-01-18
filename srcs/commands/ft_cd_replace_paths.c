/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_replace_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:45:48 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/08 12:45:50 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * При отсутствии переменной OLDPWD в списке переменных окружения
 * функция создает новый элемент, устанавливает ему значения на основе
 * ключа OLDPWD, а так же содержимого из корневой переменной past_dir
 * и добавляет новый узел в конец списка.
 * Иначе (при наличии переменной) просто обновляет ее значения.
 *
 * @param shell - корневая структура, откуда вытаскивается информация.
 */
static void	create_old_pwd(t_data *shell)
{
	t_env_list	*node;
	char		*key;
	char		*value;
	char		*str;
	char		*tmp;

	tmp = NULL;
	node = get_node_by_content(shell->env_node, "OLDPWD", 0);
	if (!node)
	{
		key = ft_strdup("OLDPWD");
		value = ft_strdup(shell->past_dir);
		str = ft_strjoin(key, ft_strjoin("=", value, -1), 1);
		push_back(&shell->env_node, key, value, str);
	}
	else
	{
		tmp = node->value;
		node->value = ft_strdup(shell->past_dir);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin(node->key,
				ft_strjoin("=", node->value, -1), 1);
		free(tmp);
	}
}

int	ft_cd_replace_paths(t_data *shell)
{
	create_old_pwd(shell);
	chdir(shell->curr_dir);
	if (chdir(shell->curr_dir) < 0)
	{
		perror(shell->curr_dir);
		return (1);
	}
	return (0);
}
