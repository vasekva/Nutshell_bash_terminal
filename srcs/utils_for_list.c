/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 23:35:59 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/06 23:36:00 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Функция проходится по элементам списка и ищет в узлах совпадения по ключу
 *
 * @param list:	список, в котором производится поиск
 * @param key:	искомый ключ
 *
 * @return возвращает указатель на value из узла, в котором ключ равен искомому
 * Возвращает NULL, если искомый ключ не найден
 */
char	*get_value_by_key(t_env_list *list, char *key)
{
	t_env_list	*env_node;

	env_node = list;
	while (env_node)
	{
		if (!ft_strncmp(key, env_node->key, ft_strlen(env_node->key)))
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}

/**
 * Функция ищет элемент в списке по его содержимому, искомый элемент
 * зависит от значения параметра flag:
 * если flag == 0 - поиск совпадения поля key
 * если flag == 1 - поиск совпадения поля value
 *
 * @param list:	список, в котором производится поиск
 * @param content:	содержимое, которое необходимо найти
 * @param flag: идентификатор подхода поиска
 *
 * @return возвращает звено, в котором найден нужный контент
 * Возвращает NULL, если искомый контент не найден
 */
t_env_list	*get_node_by_content(t_env_list *list, char *content, int flag)
{
	t_env_list	*e_node;

	if (!list)
		return (NULL);
	e_node = list;
	while (e_node)
	{
		if (flag == 0)
		{
			if (!ft_strncmp(content, e_node->key, ft_strlen(e_node->key)))
				return (e_node);
		}
		else if (flag == 1)
		{
			if (!ft_strncmp(content, e_node->value, ft_strlen(e_node->value)))
				return (e_node);
		}
		else if (flag == 2)
		{
			if (!ft_strncmp(content, e_node->str, ft_strlen(e_node->str)))
				return (e_node);
		}
		e_node = e_node->next;
	}
	return (NULL);
}

void	free_node_content(t_env_list *node)
{
	if (!node)
		return ;
	node->next = NULL;
	node->past = NULL;
	free(node->key);
	free(node->value);
	free(node->str);
	free(node);
	node = NULL;
}

static	void	swap_list_values(t_env_list *a, t_env_list *b)
{
	char	*str;
	char	*key;
	char	*value;

	str = a->str;
	key = a->key;
	value = a->value;
	a->str = b->str;
	a->key = b->key;
	a->value = b->value;
	b->str = str;
	b->key = key;
	b->value = value;
}

void	list_sort(t_env_list *list)
{
	t_env_list	*external_node;
	t_env_list	*internal_node;
	char		*external_str;
	char		*internal_str;

	external_node = list;
	internal_node = list->next;
	external_str = NULL;
	internal_str = NULL;
	while (external_node->next)
	{
		while (internal_node->next)
		{
			internal_str = internal_node->str;
			external_str = external_node->str;
			if (ft_strncmp_old(internal_str, external_str, \
								ft_strlen(external_str)) == -1)
			{
				swap_list_values(external_node, internal_node);
			}
			internal_node = internal_node->next;
		}
		internal_node = external_node->next;
		external_node = external_node->next;
	}
}
