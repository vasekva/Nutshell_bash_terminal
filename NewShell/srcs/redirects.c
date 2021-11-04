/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:22:34 by atory             #+#    #+#             */
/*   Updated: 2021/11/04 20:23:26 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "minishell.h"

static void	heredoc_redirect(t_cmd *node, t_redir_list *rdr)
{
	printf("{heredoc}\n");
}

static void	classic_redirect(t_cmd *node, t_redir_list *rdr)
{
	int	fd;

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

void	open_filenames_fd(t_cmd *node)
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
