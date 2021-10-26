//
// Created by Achiote Tory on 10/25/21.
//

#include "fcntl.h"
#include "minishell.h"

static void	double_redirect_input(t_cmd *node, char *filename)
{
	printf("{heredoc}\n");
}

static void	double_redirect_output(t_cmd *node, char *filename)
{
	int	i;
	int	fd;

	i = 0;
	while (filename[i] == ' ' || filename[i] == '>')
		i++;
	fd = open(&filename[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exception(NULL, NULL, OPEN_FD_ERROR);
	node->fd_output = fd;
}

static void	redirect_output(t_cmd *node, char *filename)
{
	int	i;
	int	fd;

	i = 0;
	while (filename[i] == ' ' || filename[i] == '>')
		i++;
	fd = open(&filename[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		exception(NULL, NULL, OPEN_FD_ERROR);
	node->fd_output = fd;
}

static void	redirect_input(t_cmd *node, char *filename)
{
	int	i;
	int	fd;

	i = 0;
	while (filename[i] == ' ' || filename[i] == '<')
		i++;
	fd = open(&filename[i], O_CREAT | O_RDONLY, 0666);
	if (fd < 0)
		exception(NULL, NULL, OPEN_FD_ERROR);
	node->fd_input = fd;
}

void	open_filenames_fd(t_cmd *node) // не обработаны кейсы 2>&1
{
	t_redir_list	*ptr;

	ptr = node->r_list;
	while (ptr)
	{
		if (ptr->filename[0] == '<' && ptr->filename[0] == ptr->filename[1])
			double_redirect_input(node, ptr->filename);
		else if (ptr->filename[0] == '>' && \
		ptr->filename[0] == ptr->filename[1])
			double_redirect_output(node, ptr->filename);
		else if (ptr->filename[0] == '>')
			redirect_output(node, ptr->filename);
		else if (ptr->filename[0] == '<')
			redirect_input(node, ptr->filename);
		ptr = ptr->next;
	}
}
