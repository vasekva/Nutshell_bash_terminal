//
// Created by atory on 24.10.2021.
//

#include "minishell.h"

static t_redir_list	*create_elem(char *filename)
{
	t_redir_list	*new;

	new = NULL;
	new = malloc(sizeof(t_redir_list));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->next = NULL;
	return (new);
}

static void	add_back(t_redir_list **head, t_redir_list *new)
{
	t_redir_list	*temp;

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

char	*cut_filenames(char **str, int *i, int len)
{
	char	*s;
	char	*tmp;
	char	*filename;

	s = *str;
	len += (s[*i + len] && s[*i + len] == s[*i]);
	while (s[*i + len] && s[*i + len] == ' ')
		len++;
	while (s[*i + len] && s[*i + len] != ' ' && s[*i + len] != '>' && \
		s[*i + len] != '<' && s[*i + len] != '"' && s[*i + len] != '\'')
		len++;
	filename = ft_substr(s, *i, len);
	if (!filename)
		exception(NULL, NULL, MALLOC_ERROR);
	tmp = ft_replace_dollar(s, *i, *i + len, "");
	free(*str);
	*str = tmp;
	(*i)--;
	return (filename);
}

void	refactor_redirects(char **line, t_redir_list **r_list)
{
	char			*str;
	int				i;
	int				s_q_flag;
	int				d_q_flag;
	t_redir_list	*ptr;

	s_q_flag = 0;
	d_q_flag = 0;
	str = *line;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			switcher(str[i], &d_q_flag, &s_q_flag);
		if ((str[i] == '>' || str[i] == '<') && !d_q_flag && !s_q_flag)
		{
			ptr = create_elem(cut_filenames(&str, &i, 1));
			add_back(r_list, ptr);
		}
	}
	*line = str;
}
