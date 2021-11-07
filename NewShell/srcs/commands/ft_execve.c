/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 23:34:35 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/06 23:34:37 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_directory(char *path, char *cmd)
{
	DIR				*direct;
	struct dirent	*dir_file;

	direct = opendir(path);
	if (!direct)
		return (NULL);
	dir_file = readdir(direct);
	while (dir_file)
	{
		if (ft_strncmp(dir_file->d_name, cmd, ft_strlen(cmd) + 4) == 0)
		{
			closedir(direct);
			return (ft_strjoin("/", dir_file->d_name, -1));
		}
		dir_file = readdir(direct);
	}
	closedir(direct);
	return (NULL);
}

static char	*define_of_dir(t_data *shell)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*cmd_path;

	i = -1;
	if (!shell->env_node)
		return (NULL); //TODO оригинальный bash выводит "No such file or directory"
	cmd_path = get_value_by_key(shell->env_node, "PATH");
	if (!cmd_path)
		return (NULL);
	paths = ft_split(cmd_path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		cmd_path = check_directory(paths[i], shell->list_cmds->command[0]);
		if (cmd_path)
		{
			cmd = ft_strjoin(paths[i], cmd_path, -1);
			free(cmd_path);
			arr_free(paths);
			return (cmd);
		}
	}
	arr_free(paths);
	return (cmd_path);
}

/**
 * Функция проходится по узлам списка и копирует их в двумерный массив.
 *
 * @param list:	список, в котором производится поиск.
 *
 * @return возвращает двумерный массив, полученный путем прохода
 * по узлам списка и копирования (list->str) значений.
 */
static char	**get_envp_copy(t_data *shell)
{
	int			length;
	int			i;
	char		**env_copy;
	t_env_list	*node;

	i = 0;
	if (!shell->env_node)
		return (NULL);
	length = list_length(shell->env_node);
	env_copy = (char **)malloc(sizeof(char *) * length + 1);
	if (!env_copy)
		exception(NULL, NULL, MALLOC_ERROR);
	env_copy[length] = NULL;
	node = shell->env_node;
	while (node)
	{
		env_copy[i] = ft_strdup(node->str);
		if (!env_copy[i])
			exception(NULL, NULL, MALLOC_ERROR);
		node = node->next;
		i++;
	}
	return (env_copy);
}

static void	execute(t_data *shell, t_cmd *node, char *cmd_path, char **argv)
{
	pid_t	status;
	char	**env_copy;
	t_env_list *tmp_node;

	env_copy = NULL;
	tmp_node = get_node_by_content(shell->env_node, "PATH", 0);
	if (!tmp_node)
	{
		exception(node->command[0], NULL, NO_FILE_OR_DIR);
		return ;
	}
	set_signal_handler(CHILD); // TODO: ПОСМОТРЕТЬ СЮДА
	status = fork();
	if (status == 0)
	{
		env_copy = get_envp_copy(shell);
		if (!env_copy)
			return ; // TODO: No such file or directory????
		execve(cmd_path, argv, env_copy);
		arr_free(env_copy);
		exception(cmd_path, NULL, CMD_NOT_FOUND);
		exit(1);
	}
	status = wait(&status);
	set_signal_handler(PARENT); // TODO: ПОСМОТРЕТЬ СЮДА
}

void	ft_execve(t_data *shell, t_cmd *node)
{
	char	*cmd_path;
	char	**argv;

	argv = node->command;
	cmd_path = define_of_dir(shell);
	if (cmd_path)
		execute(shell, node, cmd_path, argv);
	else
		execute(shell, node, argv[0], argv);
	free(cmd_path);
}
