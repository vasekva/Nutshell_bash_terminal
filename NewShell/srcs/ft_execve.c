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

char	*def_dir(t_cmd *s_cmd)
{
	int		i;
	char	**paths;
	char	*line;
	char	*tmp;

	i = -1;
	tmp = env_get_value_by_key(s_cmd->envp_copy, "PATH");
	paths = ft_split(tmp, ':');
	while (paths[++i])
	{
		tmp = verify_dir(paths[i], s_cmd->command[0]);
		if (tmp)
		{
			line = ft_strjoin(paths[i], tmp, -1);
			free(tmp);
			arr_free(paths);
			return (line);
		}
	}
	if (paths)
		arr_free(paths);
	return (tmp);
}

void	ft_execute(t_cmd *s_cmd, char *path)
{
	pid_t	forks;

	forks = fork();
	if (forks == 0)
	{
		execve(path, &s_cmd->command[0], s_cmd->envp_copy);
		exception(FIVE);
		exit(1);
	}
	forks = wait(&forks);
}

void	ft_execve(t_cmd *s_cmd)
{
	char	*path;

	path = def_dir(s_cmd);
	ft_execute(s_cmd, path);
}