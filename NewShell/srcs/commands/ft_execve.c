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
			return (ft_strjoin("/", dir_file->d_name, -1)); //todo: возможно лики
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
	paths = ft_split(cmd_path, ':');
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
	env_copy = (char **)malloc(sizeof(char*) * length + 1);
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

static void	execute(t_data *shell, char *cmd_path)
{
	pid_t	status;
	char	**env_copy;

	status = fork();
	env_copy = NULL;
	if (status == 0)
	{
		env_copy = get_envp_copy(shell);
		if (!env_copy)
			return ; // TODO: No such file or directory????
		execve(cmd_path, &shell->list_cmds->command[0], env_copy);
		arr_free(env_copy);
		exception(cmd_path, NULL, CMD_NOT_FOUND);
		exit(1);
	}
	status = wait(&status);
}

void	ft_execve(t_data *shell)
{
	char	*cmd_path;

	cmd_path = define_of_dir(shell);
	if (cmd_path)
		execute(shell, cmd_path);
	else
		execute(shell, shell->list_cmds->command[0]);
	free(cmd_path);
}