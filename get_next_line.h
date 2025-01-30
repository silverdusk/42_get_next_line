/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <kmatskev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:48 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/30 19:26:59 by kmatskev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

// ================== get_next_line_utils.c ==================
size_t		ft_strlen(const char *s);
int			ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_allocate_new_str(size_t s1_len, size_t len);

// ===================== get_next_line.c =====================
int			refill_buffer(int fd, char *buf, char **line);
int			buffer_initializer(int fd, char *buf, char **line);
char		*ft_strnjoin(char *s1, char *s2, size_t len);
void		*ft_buffmove(char *buf, size_t start);
char		*get_next_line(int fd);

#endif
