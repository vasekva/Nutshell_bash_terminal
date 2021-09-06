#include "minishell.h"

char	*verify_dir(char *path, char *cmd)
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

char	*def_dir(t_loginfo *shell)
{
	int		i;
	char	**paths;
	char	*line;
	char	*tmp;

	i = -1;
	tmp = env_get_value_by_key(shell->commands->envp_copy, "PATH");
	paths = ft_split(tmp, ':'); // todo: check split
	while (paths[++i])
	{
		tmp = verify_dir(paths[i], shell->commands->command[0]);
		if (tmp)
		{
			line = ft_strjoin(paths[i], tmp, -1);
			free(tmp);
			arr_free(paths);
			return (line);
		}
	}
	arr_free(paths);
	return (tmp);
}

void	print_message(t_loginfo *shell)
{
	printf("minishell: ");
	printf("%s: command not found\n", shell->commands->command[0]);
//	write(1, "\n", 1);
}

void	ft_execute(t_loginfo *shell, char *path)
{
	pid_t	forks;

	forks = fork();
	if (forks == 0)
	{
		execve(path, &shell->commands->command[0], shell->commands->envp_copy);
		print_message(shell);
//		exception(FIVE);
		exit(1);
	}
	forks = wait(&forks);
}

void	ft_execve(t_loginfo *shell)
{
	char	*path;

	path = def_dir(shell);
	ft_execute(shell, path);
}