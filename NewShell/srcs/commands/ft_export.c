/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:07:54 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:07:56 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_without_params(t_data *shell)
{
	t_env_list	*env_node;

	if (!shell->env_node)
		return ;
	env_node = shell->env_node;
	list_sort(env_node);
	while (env_node)
	{
		write(1, "declare -x ", 11);
		write(1, env_node->key, ft_strlen(env_node->key));
		if (ft_strchr(env_node->str, '='))
			write(1, "=", 1);
		if (ft_strchr(env_node->str, '='))
			write(1, "\"", 1);
		write(1, env_node->value, ft_strlen(env_node->value));
		if (ft_strchr(env_node->str, '='))
			write(1, "\"", 1);
		write(1, "\n", 1);
		env_node = env_node->next;
	}
}

/**
 * Функция добавляет в список переменных окружения новый узел,
 * заполняя его значениями key, value и str.
 * Если в полученной строке есть символ '=', то value в узле
 * будет соответствовать оставшемуся значению строки после этого знака.
 * После этого '=' заменяется на '\0', тем самым ограничивая
 * получение значения key до этого символа.
 *
 * @param shell: корневая структура, откуда берется
 * список строк, который задал пользователь для импорта.
 *
 * @param key: NULL значение, которое инициализируется новой
 * строкой от начала до '\0'.
 *
 * @param value: NULL значение, которое инициализируется новой
 * строкой от символа '=' (не включая), если оно есть и пустой
 * строкой, если его нет.
 *
 * @param str:	NULL значение, которое инициализируется копией
 * полученной строки из списка для импорта.
 *
 */
static void	add_variables(t_data *shell, char *key, char *value, char *str)
{
	char	*var;
	char	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	var = NULL;
	while (shell->list_cmds->command[++i])
	{
		var = shell->list_cmds->command[i];
		ptr = ft_strchr(shell->list_cmds->command[i], '=');
		str = ft_strdup(var);
		if (ptr)
		{
			ptr[0] = '\0';
			if (ptr[1])
				++ptr;
			value = ft_strdup(ptr);
		}
		else
			value = ft_strdup("");
		key = ft_strdup(var);
		push_back(&shell->env_node, key, value, str);
	}
}

void	ft_export(t_data *shell)
{
	char	*key;
	char	*value;
	char	*str;

	key = NULL;
	value = NULL;
	str = NULL;
	if (!shell->list_cmds->command[1]
		|| (shell->list_cmds->command[1]
			&& !ft_strlen(shell->list_cmds->command[1])
			&& !shell->list_cmds->command[2]))
	{
		export_without_params(shell);
		return ;
	}
	add_variables(shell, key, value, str);
}
