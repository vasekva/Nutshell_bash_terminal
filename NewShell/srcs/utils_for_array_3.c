#include "minishell.h"

// возвращает индекс первого совпадения символа в строке
int	get_symbol_ind(char *str, char symbol)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == symbol)
			return (i);
	}
	return (0);
}

// возвращает индекс строки в двумерном массиве по ключевому значению
int	env_find_str_ind_by_key(char **array, char *key)
{
	int i;
	int	ind;

	i = -1;
	while (array[++i] != NULL)
	{
		ind = get_symbol_ind(array[i], '=');
		if (!ft_strncmp_old(array[i], key, ind))
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * возвращает !!!не замалоченную строку, найденную в двумерном массиве по ключу \n
 * строка возвращается по указателю начиная с индекса после символа '='
 *
 * @param array	:	envp_copy array
 * @param key	:	search key
 *
 * @return возвращает указатель на значение переменной
 * @return или NULL, если такой ключ в массиве не найден
 */
char	*env_get_value_by_key(char **array, char *key)
{
	int	str_ind;
	int	symbol_ind;
	char *ret;

	str_ind = env_find_str_ind_by_key(array, key);
	if (str_ind == -1)
		return (NULL);
	symbol_ind = get_symbol_ind(array[str_ind], '=');
	symbol_ind++;
//	ret = ft_strdup(&array[str_ind][symbol_ind]);
	ret = &array[str_ind][symbol_ind];
	return (ret);
}