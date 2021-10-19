/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:03:44 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:03:46 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	changeNodeToPast(t_data *shell)
{
	char	*curr_path;
	char	*new_path;
	int		i;
	int		slash_index;
	//printf("%s\n", getcwd(NULL, 0));
	curr_path = getcwd(NULL, 0);
	new_path = NULL;
	slash_index = 0;
	i = -1;
	if (!ft_strncmp("/", curr_path, ft_strlen(curr_path)))
		return ;
	else
	{
		while (curr_path[++i])
		{
			if (curr_path[i] == '/')
				slash_index = i;
		}
		new_path = ft_substr(curr_path, 0, slash_index);
	}
	printf("RES: %s\n", new_path);
}

int	ft_cd(t_data *shell)
{
	t_cmd *s_cmd;

	if (!shell || !shell->list_cmds)
		exception(EMPTYPOINTER);
	s_cmd = shell->list_cmds;
	int i = -1;
	while (shell->list_cmds->command[++i])
		printf("%s\n", shell->list_cmds->command[i]);
	if (!ft_strncmp("..", s_cmd->command[1], ft_strlen(s_cmd->command[1])))
	{
		changeNodeToPast(shell);
	}

	return (0);
}
