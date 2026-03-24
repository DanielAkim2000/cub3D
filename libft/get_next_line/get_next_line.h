/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:37:53 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/22 15:34:50 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
ssize_t	ft_strchr_mod(const char *s);
char	*ft_strj(const char *s1, const char *s2, size_t *len, size_t datal);
char	*get_next_line(int fd);
ssize_t	ft_reader(int fd, char **data, char *buffer, size_t *len_data);
char	*ft_line_handler(char *data, int index);
char	*ft_data_keeper(char *data, int index);
char	*ft_eof_handler(char **data);
void	ft_var_init(ssize_t *b_read, size_t *len, int *nl_found);

#endif
