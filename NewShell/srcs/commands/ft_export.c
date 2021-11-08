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

static void	print_export_list(t_data *shell, t_cmd *node)
{
	t_env_list	*env_node;

	if (!shell->env_node)
		return ;
	env_node = shell->env_node;
	list_sort(env_node);
	while (env_node)
	{
		ft_putstr_fd(node->fd_output, "declare -x ", 0);
		ft_putstr_fd(node->fd_output, env_node->key, 0);
		if (ft_strchr(env_node->str, '='))
			write(node->fd_output, "=", 1);
		if (ft_strchr(env_node->str, '='))
			write(node->fd_output, "\"", 1);
		ft_putstr_fd(node->fd_output, env_node->value, 0);
		if (ft_strchr(env_node->str, '='))
			write(node->fd_output, "\"", 1);
		write(node->fd_output, "\n", 1);
		env_node = env_node->next;
	}
}

static int	key_check(char *variable)
{
	int		i;
	char	c;

	i = -1;
	while (variable[++i] && variable[i] != '=')
	{
		c = variable[i];
		if (ft_isdigit(c) || (!ft_isalpha(c) && c != '_'))
		{
			exception("export", variable, INVALID_IDENT);
			return (-1);
		}
	}
	return (1);
}

/**
 * Вспомогательная функция для change_export_list(), которая выполняет
 * основную логику замены, либо добавления узла в список.
 *
 * Сначала проверяется, если ли значение с таким ключом в списке, если нет, то
 * в список добавляется новый узел, иначе при наличии символа '=' в строке
 * импорта меняет значение в найденом узле.
 */
static void	define_how_to_add(t_data *shell, char *key, char *value, char *str)
{
	t_env_list	*check_ptr;
	char		*tmp;

	check_ptr = get_node_by_content(shell->env_node, key, 0);
	if (!check_ptr)
		push_back(&shell->env_node, key, value, str);
	else
	{
		if (ft_strchr(str, '='))
		{
			tmp = check_ptr->value;
			check_ptr->value = ft_strdup(value);
			free(tmp);
			tmp = check_ptr->str;
			check_ptr->str = ft_strjoin(check_ptr->key, ft_strjoin("=",
						check_ptr->value, -1), 1);
			free(tmp);
		}
		free(key);
		free(value);
		free(str);
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
 * Если переменная с таким key уже есть в списке, то меняется
 * только значение.
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
static void	change_export_list(t_data *shell, char *key, char *value, char *str)
{
	char	*var;
	char	*ptr;
	int		i;

	i = 0;
	while (shell->list_cmds->command[++i])
	{
		if (key_check(shell->list_cmds->command[i]) != -1)
		{
			var = shell->list_cmds->command[i];
			ptr = ft_strchr(shell->list_cmds->command[i], '=');
			str = ft_strdup(shell->list_cmds->command[i]);
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
			define_how_to_add(shell, key, value, str);
		}
	}
}

void	ft_export(t_data *shell, t_cmd *node)
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
		print_export_list(shell, node);
		return ;
	}
	change_export_list(shell, key, value, str);
}
