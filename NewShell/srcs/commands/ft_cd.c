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
 * Функция проверяет наличие переменной окружения по
 * ключевому значению dst_path_key, при ее наличии меняет значение
 * этой переменой на значение new_path.
 * Так же вне зависимости от результата первого действия
 * обновляет переменные curr_dir и past_dir в корневой структуре.
 *
 * Если переменной назначения нет в списке, то производится только
 * смена переменных в корневой структуре, отвечающих за текущий путь
 * и путь, который был перед изменением.
 *
 * @param shell - корневая структура, откуда вытаскивается информация.
 *
 * @param new_path - значение пути, которое копируется и назначается новым
 * текущим положением.
 *
 * @param dst_path_key - ключ, по которому производится поиск элемента списка
 * (переменной окружения) в которую будет копироваться значение new_path.
 */
static void	change_dirs(t_data *shell, char *new_path, char *dst_path_key)
{
	t_env_list	*node;
	char		*path;
	char		*tmp;

	if (!ft_strncmp_old(shell->curr_dir, new_path,
			ft_strlen(new_path)))
		return ;
	path = ft_strdup(new_path);
	node = get_node_by_content(shell->env_node, dst_path_key, 0);
	if (node)
	{
		tmp = node->value;
		node->value = ft_strdup(path);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin(dst_path_key, node->value, -1);
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
 * Функция копирует значение(путь) из переменной(элемента списка),
 * полученной по src_key в значение переменной(элемента списка),
 * найденной по dst_key.
 *
 * 1) Проверяется наличие переменной по ключу src_key, если ее нет
 * - исключение
 * 2) Получаем элемент списка переменной
 *
 * Если искомой переменной нет, то выдается исключение, иначе
 * дальнейшее выполнение делегируется функции change_dirs()
 * которая меняет текущую директорию на значение переменной HOME.
 *
 * @param shell - корневая структура, откуда передается информация.
 *
 * @param src_key: Ключ, по которому производится поиск переменной
 * из которой копируется значение.
 *
 * @param dst_key: Ключ, по которому производится поиск переменной
 * в которую копируется значение.
 */
static void	change_value(t_data *shell, char *src_key, char *dst_key)
{
	t_env_list	*src_node;

	src_node = get_node_by_content(shell->env_node, src_key, 0);
	if (!src_node)
		exception("cd", src_key, EMPTYENV);
	else
	{
		change_dirs(shell, src_node->value, dst_key);
	}
}

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
		str = ft_strjoin(key, value, -1);
		push_back(&shell->env_node, key, value, str);
	}
	else
	{
		tmp = node->value;
		node->value = ft_strdup(shell->past_dir);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin(node->key, node->value, -1);
		free(tmp);
	}
}

void	relative_path(t_data *shell, t_cmd *s_cmd)
{
	//DIR				*direct;
	//struct dirent	*dir_file;

	if (s_cmd->command[1][0] == '/')
	{
		change_dirs(shell, "/", "PWD");
	}
	else if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		ft_cd_updir(shell);
	}
//	direct = opendir(path);
//	if (!direct)
//		return (NULL);
//	dir_file = readdir(direct);
}

int	ft_cd(t_data *shell)
{
	t_cmd		*s_cmd;

	if (!shell || !shell->list_cmds)
		exception(NULL, NULL, EMPTYPOINTER);
	s_cmd = shell->list_cmds;
	if (s_cmd->command[1] &&
		((s_cmd->command[1][0] == '.') || (s_cmd->command[1][0] == '/')))
		relative_path(shell, s_cmd);
	else if (!shell->env_node)
	{
		if (!s_cmd->command[1] || !ft_strncmp("--", s_cmd->command[1],
				ft_strlen(s_cmd->command[1])))
			exception(s_cmd->command[0], "HOME", EMPTYENV);
		else if (!ft_strncmp("-", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
			exception(s_cmd->command[0], "OLDPWD", EMPTYENV);
		return (0);
	}
	else if (!s_cmd->command[1] || !ft_strncmp("--", s_cmd->command[1],
		ft_strlen(s_cmd->command[1])))
	{
		change_value(shell, "HOME", "PWD");
	}
	else if (!ft_strncmp("-", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		change_value(shell, "OLDPWD", "PWD");
	}
	create_old_pwd(shell);
	return (0);
}
