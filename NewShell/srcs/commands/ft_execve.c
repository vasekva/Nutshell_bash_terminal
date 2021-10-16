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
	char	*tmp;

	i = -1;
	tmp = get_value_by_key(shell->env_node, "PATH");
	paths = ft_split(tmp, ':');
	while (paths[++i])
	{
		tmp = check_directory(paths[i], shell->list_cmds->command[0]);
		if (tmp)
		{
			cmd = ft_strjoin(paths[i], tmp, -1);
			free(tmp);
			arr_free(paths);
			return (cmd);
		}
	}
	arr_free(paths);
	return (tmp);
}

static void	print_message(t_data *shell)
{
	printf("minishell: ");
	printf("%s: command not found\n", shell->list_cmds->command[0]);
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
	length = list_length(shell->env_node);
	env_copy = (char **)malloc(sizeof(char*) * length + 1);
	if (!env_copy)
		exception(MALLOC_ERROR);
	env_copy[length] = NULL;
	node = shell->env_node;
	while (node)
	{
		env_copy[i] = ft_strdup(node->str);
		if (!env_copy[i])
			exception(MALLOC_ERROR);
		node = node->next;
		i++;
	}
	return (env_copy);
}

static void	execute(t_data *shell, char *command)
{
	pid_t	forks;
	char	**env_copy;

	forks = fork();
	env_copy = NULL;
	if (forks == 0)
	{
		env_copy = get_envp_copy(shell);
		execve(command, &shell->list_cmds->command[0], env_copy);
		arr_free(env_copy);
		print_message(shell);
		exit(1);
	}
	forks = wait(&forks);
}

void	ft_execve(t_data *shell)
{
	char	*cmd;

	cmd = define_of_dir(shell);
	if (cmd)
		execute(shell, cmd);
	else
		execute(shell, shell->list_cmds->command[0]);
	free(cmd);
}