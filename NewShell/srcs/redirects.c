//
// Created by Achiote Tory on 10/25/21.
//

#include "fcntl.h"
#include "minishell.h"

static void	heredoc_redirect(t_cmd *node, t_redir_list *rdr)
{
	printf("{heredoc}\n");
}

static void classic_redirect(t_cmd *node, t_redir_list *rdr)
{
	int	fd;

	printf("%s\n", rdr->filename);
	if (rdr->type == REDIRECT_INPUT)
	{
		fd = open(rdr->filename, O_CREAT | O_RDONLY, 0664);
		if (fd < 0)
			exception(NULL, NULL, OPEN_FD_ERROR);
		node->fd_input = fd;
	}
	else if (rdr->type == REDIRECT_OUTPUT)
	{
		fd = open(rdr->filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (fd < 0)
			exception(NULL, NULL, OPEN_FD_ERROR);
		node->fd_output = fd;
	}
	else
	{
		fd = open(rdr->filename, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (fd < 0)
			exception(NULL, NULL, OPEN_FD_ERROR);
		node->fd_output = fd;
	}
}

void	open_filenames_fd(t_cmd *node) // не обработаны кейсы 2>&1
{
	t_redir_list	*ptr;

	ptr = node->r_list;
	while (ptr)
	{
		if (ptr->type != REDIRECT_INPUT_HEREDOC)
			classic_redirect(node, ptr);
		else
			heredoc_redirect(node, ptr);
		ptr = ptr->next;
	}
}
