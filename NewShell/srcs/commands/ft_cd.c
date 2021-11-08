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

static void	change_curr_path(t_data *shell, t_cmd *s_cmd)
{
	int	ret;

	ret = 0;
	if (s_cmd->command[1][0] == '/')
	{
		if (ft_strlen(s_cmd->command[1]) == 1)
			change_dirs(shell, "/", "PWD");
		else
		{
			ret = has_file(s_cmd->command[1]);
			if (s_cmd->command[1][ft_strlen(s_cmd->command[1]) - 1] == '/')
			{
				s_cmd->command[1][ft_strlen(s_cmd->command[1]) - 1] = '\0';
			}
			if (ret == 1)
				change_dirs(shell, s_cmd->command[1], "PWD");
		}
	}
	else if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
		ft_cd_updir(shell);
	else
		relative_path(shell, s_cmd);
}

static int	cd_execute(t_data *shell, t_cmd *node, char *cd_cmd, int len_of_cmd)
{
	int	ret;

	if (cd_cmd && (ft_strncmp("-", cd_cmd, len_of_cmd)
			&& (ft_strncmp("--", cd_cmd, len_of_cmd))))
		change_curr_path(shell, node);
	else if (!shell->env_node)
	{
		if (!cd_cmd || !ft_strncmp("--", cd_cmd, len_of_cmd))
			exception("cd", "HOME", EMPTYENV);
		else if (!ft_strncmp("-", cd_cmd, len_of_cmd))
			exception("cd", "OLDPWD", EMPTYENV);
		ret = 1;
	}
	else if (!cd_cmd || !ft_strncmp("--", cd_cmd, len_of_cmd))
		ret = change_value(shell, "HOME", "PWD");
	else if (!ft_strncmp("-", cd_cmd, len_of_cmd))
	{
		ret = change_value(shell, "OLDPWD", "PWD");
		if (!ret)
			ft_putstr_fd(node->fd_output, shell->curr_dir, 1);
	}
	if (ft_cd_replace_paths(shell))
		ret = 1;
	return (ret);
}

int	ft_cd(t_data *shell, t_cmd *node)
{
	char		*cd_cmd;
	int			len_of_cmd;
	int			ret;

	if (!shell || !shell->list_cmds)
		exception(NULL, NULL, EMPTYPOINTER);
	ret = 0;
	cd_cmd = NULL;
	len_of_cmd = 0;
	if (node->command[1])
	{
		cd_cmd = node->command[1];
		len_of_cmd = ft_strlen(cd_cmd);
	}
	ret = cd_execute(shell, node, cd_cmd, len_of_cmd);
	return (ret);
}
