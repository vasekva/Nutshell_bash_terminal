#include "header_for_tests.h"

int	test_get_symbol_ind(char *str, char *symbol)
{
	char *found = strstr(str, symbol);
	int	index;

	index = -1;
	if (found != NULL)
	{
		index = found - str;
	}
	if (index == get_symbol_ind(str, symbol[0]))
		return (1);
	else
		return (0);
}

int	test_env_find_str_ind_by_key(void)
{
	char **array = (char **)malloc(sizeof(char *) * 6);
	array[0] = ft_strdup("SHLVL=1");
	array[1] = ft_strdup("HOME=/Users/jberegon");
	array[2] = ft_strdup("LOGNAME=jberegon");
	array[3] = ft_strdup("PAGER=less");
	array[4] = ft_strdup("XPC_FLAGS=0x0");
	array[5] = NULL;

	if (env_find_str_ind_by_key(array, "SHLVL") == 0
		&& env_find_str_ind_by_key(array, "HOME") == 1
		&& env_find_str_ind_by_key(array, "LOGNAME") == 2
		&& env_find_str_ind_by_key(array, "HELLO") == -1
		&& env_find_str_ind_by_key(array, "XPC_FLAGS") == 4
	)
		return (1);
	else
		return (0);
}

int	test_env_get_value_by_key(void)
{
	char **array = (char **)malloc(sizeof(char *) * 6);
	array[0] = ft_strdup("SHLVL=1");
	array[1] = ft_strdup("HOME=/Users/jberegon");
	array[2] = ft_strdup("LOGNAME=jberegon");
	array[3] = ft_strdup("PAGER=less");
	array[4] = ft_strdup("XPC_FLAGS=0x0");
	array[5] = NULL;

	char *str_1 = env_get_value_by_key(array, "SHLVL");
	char *str_2 = env_get_value_by_key(array, "HOME");
	char *str_3 = env_get_value_by_key(array, "LOGNAME");
	if (ft_strncmp(str_1, "1", ft_strlen(str_1)) == 0
		&& ft_strncmp(str_2, "/Users/jberegon", ft_strlen(str_2)) == 0
		&& ft_strncmp(str_3, "jberegon", ft_strlen(str_3)) == 0
		)
		return (1);
	else
		return (0);
}


void	printSuccessMessage(void)
{
	printf("TEST SUCCUESS!!\n");
}

int main(int argc, char **argv)
{

	if (argc <= 1)
	{
		printf("Задай больше параметров!\n");
		return (-1);
	}
// if (test_get_symbol_ind(argv[1], argv[2]))
//		printSuccessMessage();
//	if (test_env_find_str_ind_by_key())
//		printSuccessMessage();
	if (test_env_get_value_by_key())
		printSuccessMessage();
	return (0);
}