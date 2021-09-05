//
// Created by Josephine Beregond on 9/4/21.
//

#ifndef NEWSHELL_HEADER_FOR_TESTS_H
#define NEWSHELL_HEADER_FOR_TESTS_H

#include "minishell.h"

#include <string.h>
#include <stdio.h>

int	get_symbol_ind(char *str, char symbol);
int	env_find_str_ind_by_key(char **array, char *key);
char *env_get_value_by_key(char **array, char *key);


#endif //NEWSHELL_HEADER_FOR_TESTS_H
