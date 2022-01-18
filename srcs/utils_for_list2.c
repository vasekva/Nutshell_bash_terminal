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

/**
 * Функция возвращает
 * длину полученного списка.
 */
int	list_length(const t_env_list *list)
{
	int	length;

	length = 0;
	while (list)
	{
		list = list->next;
		length++;
	}
	return (length);
}

/**
 * Функция возвращает указатель на
 * последний элемент списка.
 *
 * @return
 * Возвращает указатель на последний
 * элемент списка.\n
 * Если список равен NULL - возвращается NULL.
 */
t_env_list	*get_last(t_env_list *env_node)
{
	if (!env_node)
		return (NULL);
	while (env_node->next)
		env_node = env_node->next;
	return (env_node);
}

/**
 * Функция создает новый элемент с
 * переданными в параметрах значениями и
 * вставляет его в конец списка.
 *
 * Если список пуст - создает первый узел
 * с пустыми указателями на предыдущий и следующий узлы.
 *
 * В новом элементе сохраняется указатель
 * на предыдущее значение и устанавливается
 * NULL для следующего.
 *
 * @param env_node: Список(**), в который
 * производится вставка.
 *
 * @param key: Значение до знака '='.
 *
 * @param value: Значение после знака '='.
 *
 * @param str: Переменная окружения в виде (key)=(value)
 */
void	push_back(t_env_list **env_node, char *key, char *value, char *str)
{
	t_env_list	*last;
	t_env_list	*tmp;

	last = get_last(*env_node);
	if (!key || !value || !str)
		exception(NULL, NULL, EMPTYPOINTER);
	if (!last)
	{
		(*env_node) = (t_env_list *)malloc(sizeof(t_env_list));
		(*env_node)->key = key;
		(*env_node)->value = value;
		(*env_node)->str = str;
		(*env_node)->next = NULL;
		(*env_node)->past = NULL;
	}
	else
	{
		tmp = (t_env_list *)malloc(sizeof(t_env_list));
		tmp->key = key;
		tmp->value = value;
		tmp->str = str;
		tmp->next = NULL;
		tmp->past = last;
		last->next = tmp;
	}
}
