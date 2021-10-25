//
// Created by atory on 21.09.2021.
//

#include "minishell.h"

static t_cmd	*create_elem(char **command, t_redir_list *r)
{
	t_cmd	*new;

	new = NULL;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->fd_input = 0;
	new->fd_output = 1;
	new->command = command;
	new->num_args = 0;
	while (new->command[new->num_args])
		new->num_args++;
	if (r)
		new->is_redirect = 1;
	else
		new->is_redirect = 0;
	new->r_list = r;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

static void	add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*temp;

	if (*head == NULL)
		*head = new;
	else
	{
		temp = (*head);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

static void	create_list(t_data *shell, char *line, int index)
{
	char			**all_cmds;
	char			**final_cmds;
	t_cmd			*new_node;
	t_redir_list	*r_list;

	all_cmds = split_arguments(line, '|');
	if (!all_cmds)
		exception(NULL, NULL, SPLIT_ERROR);
	final_cmds = NULL;
	while (all_cmds[++index])
	{
		r_list = NULL;
		refactor_redirects(&all_cmds[index], &r_list);
		final_cmds = split_arguments(all_cmds[index], ' ');
		if (!final_cmds)
			exception(NULL, NULL, SPLIT_ERROR);
		new_node = create_elem(final_cmds, r_list);
		if (!new_node)
			exception(NULL, NULL, MALLOC_ERROR);
		add_back(&shell->list_cmds, new_node);
	}
	arr_free(all_cmds);
}

/*
 * разбивает входящую команду по пайпам на лист
 * очищает каждый аргумент в листе от кавычек и $
 */
void	preparser(t_data *shell, char *line)
{
	int		index;
	t_cmd	*list_ptr;
	char	*clear_line;

	create_list(shell, line, -1);
	list_ptr = shell->list_cmds;
	while (list_ptr != NULL)
	{
		index = -1;
		while (list_ptr->command[++index])
		{
			clear_line = lexer(shell, list_ptr->command[index]);
			free(list_ptr->command[index]);
			list_ptr->command[index] = clear_line;
		}
		list_ptr = list_ptr->next;
	}
}
