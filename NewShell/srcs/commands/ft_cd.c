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
void	change_dirs(t_data *shell, char *new_path, char *dst_path_key)
{
	t_env_list	*node;
	char		*path;
	char		*tmp;

	if (!ft_strncmp_old(shell->curr_dir, new_path, ft_strlen(new_path)))
		return ;
	path = ft_strdup(new_path);
	node = get_node_by_content(shell->env_node, dst_path_key, 0);
	if (node)
	{
		tmp = node->value;
		node->value = ft_strdup(path);
		free(tmp);
		tmp = node->str;
		node->str = ft_strjoin(dst_path_key,
				ft_strjoin("=", node->value, -1), 1);
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
 * Функция с помощью src_key проверяет наличие переменной в
 * списке, если искомой переменной нет, то выдается исключение, иначе
 * дальнейшее выполнение делегируется функции change_dirs(),
 * которая копирует значение(value) из узла найденного по src_key
 * в узел с значением ключа dst_key
 *
 * @param shell - корневая структура, откуда передается информация.
 *
 * @param src_key: Ключ, по которому производится поиск переменной
 * из которой копируется значение.
 *
 * @param dst_key: Ключ, по которому производится поиск переменной
 * в которую копируется значение.
 */
static int	change_value(t_data *shell, char *src_key, char *dst_key)
{
	t_env_list	*src_node;

	src_node = get_node_by_content(shell->env_node, src_key, 0);
	if (!src_node)
	{
		exception("cd", src_key, EMPTYENV);
		return (1);
	}
	else
	{
		change_dirs(shell, src_node->value, dst_key);
		return (0);
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

void	absolute_path(t_data *shell, t_cmd *s_cmd)
{
	int		res;

	res = has_file(s_cmd->command[1]);
	if (res == 1)
		change_dirs(shell, s_cmd->command[1], "PWD");
}

void	deff_change_path(t_data *shell, t_cmd *s_cmd)
{
	if (s_cmd->command[1][0] == '/')
	{
		if (ft_strlen(s_cmd->command[1]) == 1)
			change_dirs(shell, "/", "PWD");
		else
			absolute_path(shell, s_cmd);
	}
	else if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		ft_cd_updir(shell);
	}
	else
		relative_path(shell, s_cmd);
}

int	ft_cd(t_data *shell, t_cmd *node)
{
	char		*cd_cmd;
	int			len_of_cmd;
	int			ret;

	ret = 0;
	if (!shell || !shell->list_cmds)
		exception(NULL, NULL, EMPTYPOINTER);
	cd_cmd = NULL;
	if (node->command[1])
	{
		cd_cmd = node->command[1];
		len_of_cmd = ft_strlen(cd_cmd);
	}
	if (cd_cmd
		&& (ft_strncmp("-", cd_cmd, len_of_cmd)
			&& (ft_strncmp("--", cd_cmd, len_of_cmd))))
		deff_change_path(shell, node);
	else if (!shell->env_node)
	{
		if (!cd_cmd || !ft_strncmp("--", cd_cmd, len_of_cmd))
			exception("cd", "HOME", EMPTYENV);
		else if (!ft_strncmp("-", cd_cmd, len_of_cmd))
			exception("cd", "OLDPWD", EMPTYENV);
		return (0);
	}
	else if (!cd_cmd || !ft_strncmp("--", cd_cmd, len_of_cmd))
	{
		ret = change_value(shell, "HOME", "PWD"); //TODO: doesn't work
	}
	else if (!ft_strncmp("-", cd_cmd, len_of_cmd))
	{
		ret = change_value(shell, "OLDPWD", "PWD");
		if (!ret)
			printf("%s\n", shell->curr_dir);
	}
	create_old_pwd(shell);
	chdir(shell->curr_dir);
	if (chdir(shell->curr_dir) < 0)
	{
		printf("BLYAAAAA: %d\n", errno);
		perror(shell->curr_dir);
	}
	return (ret);
}
