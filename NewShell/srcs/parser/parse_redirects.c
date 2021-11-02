//
// Created by atory on 24.10.2021.
//

#include "minishell.h"

static int	define_redirect_type(char *filename)
{
	if (filename[0] == '>')
	{
		if (filename[0] == filename[1])
			return (REDIRECT_OUTPUT_DOUBLE);
		else
			return (REDIRECT_OUTPUT);
	}
	else if (filename[0] == '<')
	{
		if (filename[0] == filename[1])
			return (REDIRECT_INPUT_HEREDOC);
		else
			return (REDIRECT_INPUT);
	}
}

static t_redir_list	*create_elem(char *filename)
{
	t_redir_list	*new;
	int				i;

	new = NULL;
	new = malloc(sizeof(t_redir_list));
	if (!new)
		exception(NULL, NULL, MALLOC_ERROR);
	new->type = define_redirect_type(filename);
	i = 0;
	while (filename[i] == '>' || filename[i] == '<' || filename[i] == ' ')
		i++;
	if (filename[i] == '\'' || filename[i] == '\"')
		i++;
	new->filename = ft_substr(filename, i, ft_strlen(filename) - i - \
	(filename[i - 1] == '\'' || filename[i - 1] == '\"'));
	if (!new->filename)
		exception(NULL, NULL, MALLOC_ERROR);
	free(filename);
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

char	*cut_filenames(char **str, int *i)
{
	char	*s;
	char	*tmp;
	char	*filename;
	int		len;

	s = *str;
	len = 1;
	len += (s[*i + len] && s[*i + len] == s[*i]);
	while (s[*i + len] && s[*i + len] == ' ')
		len++;
	while (s[*i + len] && s[*i + len] != ' ' && s[*i + len] != '>' && \
	s[*i + len] != '<')
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

/**
 * функция перемещает редиректы в отдельный лист редиректов
 * и удаляет их из команды
 */
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
			ptr = create_elem(cut_filenames(&str, &i));
			add_back(r_list, ptr);
		}
	}
	*line = str;
}
