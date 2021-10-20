#include "minishell.h"

/**
 * Функция возвращает указатель на
 * последний элемент списка.
 *
 * @return
 * Возвращает указатель на последний
 * элемент списка.\n
 * Если список равен NULL - возвращается NULL.
 */
t_env_list	*get_last(t_env_list *env_node)
{
	if (!env_node)
		return (NULL);
	while (env_node->next)
		env_node = env_node->next;
	return (env_node);
}

/**
 * Функция создает новый элемент с
 * переданными в параметрах значениями и
 * вставляет его в конец списка.
 *
 * Если список пуст - создает первый узел
 * с пустыми указателями на предыдущий и следующий узлы.
 *
 * В новом элементе сохраняется указатель
 * на предыдущее значение и устанавливается
 * NULL для следующего.
 *
 * @param env_node: Список(**), в который
 * производится вставка.
 *
 * @param key: Значение до знака '='.
 *
 * @param value: Значение после знака '='.
 *
 * @param str: Переменная окружения в виде (key)=(value)
 */
void	push_back(t_env_list **env_node, char *key, char *value, char *str)
{
	t_env_list	*last;
	t_env_list	*tmp;

	last = get_last(*env_node);
	if (!key || !value || !str)
		exception(NULL, NULL, NULL, EMPTYPOINTER);
	if (!last)
	{
		(*env_node) = (t_env_list *)malloc(sizeof(t_env_list));
		(*env_node)->key = key;
		(*env_node)->value = value;
		(*env_node)->str = str;
		(*env_node)->next = NULL;
		(*env_node)->past = NULL;
	}
	else
	{
		tmp = (t_env_list *)malloc(sizeof(t_env_list));
		tmp->key = key;
		tmp->value = value;
		tmp->str = str;
		tmp->next = NULL;
		tmp->past = last;
		last->next = tmp;
	}
}

/**
 * Функция проходится по элементам списка и ищет в узлах совпадения по ключу
 *
 * @param list:	список, в котором производится поиск
 * @param key:	искомый ключ
 *
 * @return возвращает указатель на value из узла, в котором ключ равен искомому
 * Возвращает NULL, если искомый ключ не найден
 */
char	*get_value_by_key(t_env_list *list, char *key)
{
	t_env_list	*env_node;

	env_node = list;
	while (env_node)
	{
		if (!ft_strncmp(key, env_node->key, ft_strlen(env_node->key)))
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}

/**
 * Функция ищет элемент в списке по его содержимому, искомый элемент
 * зависит от значения параметра flag:
 * если flag == 0 - поиск совпадения поля key
 * если flag == 1 - поиск совпадения поля value
 *
 * @param list:	список, в котором производится поиск
 * @param content:	содержимое, которое необходимо найти
 * @param flag: идентификатор подхода поиска
 *
 * @return возвращает звено, в котором найден нужный контент
 * Возвращает NULL, если искомый контент не найден
 */
t_env_list	*get_node_by_content(t_env_list *list, char *content, int flag)
{
	t_env_list	*env_node;

	if (!list)
		return (NULL);
	env_node = list;
	while (env_node)
	{
		if (flag == 0)
		{
			if (!ft_strncmp(content, env_node->key, ft_strlen(env_node->key)))
				return (env_node);
		}
		else if (flag == 1)
		{
			if (!ft_strncmp(content, env_node->value, ft_strlen(env_node->value)))
				return (env_node);
		}
		env_node = env_node->next;
	}
	return (NULL);
}

void	free_node_content(t_env_list *node)
{
	if (!node)
		return ;
	node->next = NULL;
	node->past = NULL;
	free(node->key);
	free(node->value);
	free(node->str);
	free(node);
	node = NULL;
}
/*
void	delete_list_node(t_env_list **list)
{
	t_env_list *tmp;

	tmp = NULL;
	if (!(*list)->past)
	{
		printf("DEL FIRST\n");
		tmp = (*list);
		if ((*list)->next)
		{
			(*list) = (*list)->next;
			(*list)->past->next = NULL;
			(*list)->past = NULL;
		}
		if ((*list)->past == NULL)
			printf("PAST VALL NOW: NULL\n");
		free_node_content(tmp);
		tmp = NULL;
		if ((*list))
			printf("FIRST VAL NOW: %s\n", (*list)->str);
		(*list) = NULL;
	}
	else if (!(*list)->next)
	{
		printf("DEL LAST\n");
		(*list)->past->next = NULL;
		free_node_content((*list));
		(*list) = NULL;
	}
	else
	{
		printf("DEL MIDDLE\n");
		(*list)->past->next = (*list)->next;
		(*list)->next->past = (*list)->past;
		free_node_content((*list));
		(*list) = NULL;
	}
	if ((*list))
		printf("DA SUKA\n");
}
*/
static	void	swap_list_values(t_env_list *a, t_env_list *b)
{
	char	*str;
	char	*key;
	char	*value;

	str = a->str;
	key = a->key;
	value = a->value;
	a->str = b->str;
	a->key = b->key;
	a->value = b->value;
	b->str = str;
	b->key = key;
	b->value = value;
}

/**
 * Функция возвращает
 * длину полученного списка.
 */
int	list_length(const t_env_list *list)
{
	int	length;

	length = 0;
	while (list)
	{
		list = list->next;
		length++;
	}
	return (length);
}

void	list_sort(t_env_list *list)
{
	t_env_list	*external_node;
	t_env_list	*internal_node;
	char		*external_str;
	char		*internal_str;

	external_node = list;
	internal_node = list->next;
	external_str = NULL;
	internal_str = NULL;
	while (external_node->next)
	{
		while (internal_node->next)
		{
			internal_str = internal_node->str;
			external_str = external_node->str;
			if (ft_strncmp_old(internal_str, external_str, ft_strlen(external_str)) == -1)
			{
				swap_list_values(external_node, internal_node);
			}
			internal_node = internal_node->next;
		}
		internal_node = external_node->next;
		external_node = external_node->next;
	}
}
