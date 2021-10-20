/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:03:44 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:03:46 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Функция при наличии меняет пременную PWD и
 * значения переменных curr_dir и past_dir в корневой структуре.
 */
static void	change_dirs(t_data *shell, t_env_list *node)
{
	char		*path;
	char		*tmp;

	if (!ft_strncmp(shell->curr_dir, node->value, ft_strlen(node->value)))
		return ;
	path = ft_strdup(node->value);
	node = get_node_by_content(shell->env_node, "PWD", 0);
	if (node)
	{
		tmp = node->value;
		node->value = ft_strdup(path);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin("PWD", node->value, -1);
		free(tmp);
	}
	tmp = shell->past_dir;
	shell->past_dir = ft_strdup(shell->curr_dir);
	free(tmp);
	tmp = shell->curr_dir;
	shell->curr_dir = ft_strdup(path);
	free(path);
	free(tmp);
}

/**
 * Функция изменяет текущую директорию(местоположение) на значение
 * переменной окружения HOME.
 *
 * Если искомой переменной нет, то выдается исключение, иначе
 * дальнейшее выполнение делегируется функции change_dirs()
 * которая меняет текущую директорию на значение переменной HOME.
 *
 * @param shell: Структура в которой лежат
 * переменные текущего пути и прошлого пути.
 */
void	change_to_home(t_data *shell)
{
	t_env_list	*node;

	if (!shell)
		exception(shell, "cd", "HOME", EMPTYENV);
	else
	{
		node = get_node_by_content(shell->env_node, "HOME", 0);
		if (!node)
			exception(shell, "cd", "HOME", EMPTYENV);
		else
		{
			change_dirs(shell, node);
		}
	}
}

int	ft_cd(t_data *shell)
{
	t_cmd		*s_cmd;

	if (!shell || !shell->list_cmds)
		exception(NULL, NULL, NULL, EMPTYPOINTER);
	s_cmd = shell->list_cmds;
	if (!s_cmd->command[1])
	{
		change_to_home(shell);
	}
	else if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		ft_cd_updir(shell);
	}
	return (0);
}
