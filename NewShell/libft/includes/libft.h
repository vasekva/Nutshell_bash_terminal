/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:18:14 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:18:15 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*ft_strjoin(char *remainder, char *buff, int flag);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp_old(const char *s1, const char *s2, size_t n);

#endif
