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
 * Функция выполняет всю основную логику смены пути:
 * 1) изменяет переменные внутри структуры, отвечающие
 * за текущее местоположение и предыдщуее местоположение.
 * 2) Если есть переменная окружения, то дополнительно
 * меняет ее значение.
 */
static void	change_directory(t_data *shell, t_env_list *node, int slash_index)
{
	char	*tmp;

	tmp = NULL;
	if (shell->past_dir)
	{
		tmp = shell->past_dir;
		shell->past_dir = ft_strdup(shell->curr_dir);
		free(tmp);
	}
	tmp = shell->curr_dir;
	if (slash_index != 0)
		shell->curr_dir = ft_substr(shell->curr_dir, 0, slash_index);
	else
		shell->curr_dir = ft_strdup("/");
	free(tmp);
	if (node)
	{
		tmp = node->value;
		node->value = ft_strdup(shell->curr_dir);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin(node->key, node->value, -1);
		free(tmp);
	}
}

/**
 * Функция ищет индекс последнего слеша в строке пути
 * и делегирует дальнейшее выполнение в change_directory().
 */
static void	dirpath_up(t_data *shell, const char *curr_dir, t_env_list *node)
{
	int		i;
	int		slash_index;

	i = -1;
	slash_index = 0;
	while (curr_dir[++i])
	{
		if (curr_dir[i] == '/')
			slash_index = i;
	}
	change_directory(shell, node, slash_index);
}

/**
 * Функция изменяет текущую директорию(местоположение) на одну директорию выше.
 * example:\n
 * before: (/Users/jberegon) after: (/Users/)\n
 *
 * При вводе команды cd .. данная функция определяет
 * индекс последнего слеша и изменяет текущий путь
 * на путь до найденого слеша, изменяя переменную окружения
 * и две переменные в структуре отвечающие за текущее местоположение
 * и предыдущее местоположение.
 *
 * @param shell: Структура в которой лежат
 * переменные текущего пути и прошлого пути.
 */
void	ft_cd_updir(t_data *shell)
{
	t_env_list	*node;
	char		*curr_dir;
	char		*tmp;

	node = NULL;
	tmp = NULL;
	curr_dir = NULL;
	if (shell->env_node)
		node = get_node_by_content(shell->env_node, "PWD", 0);
	if (node)
		curr_dir = node->value;
	else
		curr_dir = shell->curr_dir;
	if (!ft_strncmp("/", curr_dir, ft_strlen(curr_dir)))
	{
		if (ft_strncmp("/", shell->past_dir, ft_strlen(shell->past_dir)))
		{
			tmp = shell->past_dir;
			shell->past_dir = ft_strdup(shell->curr_dir);
			free(tmp);
		}
		return ;
	}
	else
		dirpath_up(shell, curr_dir, node);
}
