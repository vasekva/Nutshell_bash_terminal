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

static char	*define_of_dir(t_loginfo *shell)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*tmp;

	i = -1;
	tmp = env_get_value_by_key(shell->envp_copy, "PATH");
	paths = ft_split(tmp, ':'); // todo: check split
	while (paths[++i])
	{
		tmp = check_directory(paths[i], shell->commands->command[0]);
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

static void	print_message(t_loginfo *shell)
{
	printf("minishell: ");
	printf("%s: command not found\n", shell->commands->command[0]);
}

static void	execute(t_loginfo *shell, char *command)
{
	pid_t	forks;

	forks = fork();
	if (forks == 0)
	{
		execve(command, &shell->commands->command[0], shell->envp_copy);
		print_message(shell);
		exit(1);
	}
	forks = wait(&forks);
}

void	ft_execve(t_loginfo *shell)
{
	char	*cmd;

	cmd = define_of_dir(shell);
	if (cmd)
		execute(shell, cmd);
	else
		execute(shell, shell->commands->command[0]);
}