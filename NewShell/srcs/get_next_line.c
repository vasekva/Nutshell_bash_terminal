/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:09:08 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:09:09 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_line(char *result_line)
{
	char	delimiter;
	int		len;

	len = 0;
	if (ft_strchr(result_line, '\n'))
		delimiter = '\n';
	else
		delimiter = '\0';
	while (result_line[len] != delimiter)
		len++;
	return (len);
}

char	*ft_read_line(char *remainder, int fd, int c_w_r)
{
	char	*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (!remainder)
	{
		c_w_r = read(fd, buff, BUFFER_SIZE);
		if (c_w_r < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[c_w_r] = '\0';
		remainder = ft_strdup(buff);
	}
	while (!(ft_strchr(remainder, '\n')) && c_w_r)
	{
		c_w_r = read(fd, buff, BUFFER_SIZE);
		buff[c_w_r] = '\0';
		remainder = ft_strjoin(remainder, buff, 0);
	}
	free(buff);
	return (remainder);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	int			len;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	remainder = ft_read_line(remainder, fd, 1);
	if (!remainder)
		return (-1);
	len = len_of_line(remainder);
	if (ft_strchr(remainder, '\n'))
	{
		tmp = remainder;
		*line = ft_substr(tmp, 0, len);
		remainder = ft_substr(tmp, len + 1,
				ft_strlen(remainder) - ft_strlen(*line));
		free(tmp);
		return (1);
	}
	*line = ft_substr(remainder, 0, len);
	free(remainder);
	remainder = NULL;
	return (0);
}
