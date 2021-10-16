//
// Created by atory on 21.09.2021.
//

#include "minishell.h"

static t_cmd	*create_elem(char **command)
{
	t_cmd	*new;

	new = NULL;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->command = command;
	new->num_args = 0;
	while (new->command[new->num_args])
		new->num_args++;
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
	}
}

static void	create_list(t_data *shell, char *line)
{
	char	**all_cmds;
	char	**final_cmds;
	int		index;
	t_cmd	*new_node;

	all_cmds = split_arguments(line, '|');
	if (!all_cmds)
		exception("SPLIT ERROR\n");
	index = -1;
	final_cmds = NULL;
	while (all_cmds[++index])
	{
		final_cmds = split_arguments(all_cmds[index], ' ');
		if (!final_cmds)
			exception("SPLIT ERROR\n");
		new_node = create_elem(final_cmds);
		if (!new_node)
			exception(MALLOC_ERROR);
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

	create_list(shell, line);
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
