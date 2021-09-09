/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:17:10 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:17:11 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_loginfo *shell, char *key)
{
	char	*new_value;
	char	*str;
	int		ind;
	int		i;

	i = 0;
	ind = arr_get_str_ind(shell, key);
	new_value = NULL;
	str = NULL;
	if (ind >= 0)
	{
		str = shell->envp_copy[ind];
		while (shell->envp_copy[ind][i] != '=')
		{
			i++;
		}
		new_value = ft_substr(str, i + 1, ft_strlen(str));
		return (new_value);
	}
	else
	{
		return (NULL);
	}
}

void	copy_value(t_loginfo *shell, char *src, char *dst)
{
	int		i_dst;
	char	*appended_str;
	char	*tmp_str;

	i_dst = arr_get_str_ind(shell, dst);
	appended_str = ft_strjoin(dst, "=", 3);
	appended_str = ft_strjoin(appended_str, get_value(shell, src), 2);
	tmp_str = shell->envp_copy[i_dst];
	shell->envp_copy[i_dst] = ft_strdup(appended_str);
	free(appended_str);
	free(tmp_str);
}

void	swap_values(t_loginfo *shell, char *key_fst, char *key_scnd)
{
	char	*first_value;
	char	*tmp_str;
	int		ind;

	first_value = get_value(shell, key_fst);
	copy_value(shell, key_scnd, key_fst);
	ind = arr_get_str_ind(shell, key_scnd);
	tmp_str = shell->envp_copy[ind];
	shell->envp_copy[ind] = replace_value(shell, key_scnd, first_value);
	free(tmp_str);
}

char	*replace_value(t_loginfo *shell, char *key, char *new_value)
{
	char	*new_pair;

	new_pair = ft_strjoin(key, "=", 3);
	new_pair = ft_strjoin(new_pair, new_value, 2);
	return (new_pair);
}
