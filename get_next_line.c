/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <matskevich.ke@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:35 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/23 23:11:34 by kmatskev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
	{
		return (0);
	}
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (!dst || !src)
		return (EXIT_FAILURE);
	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (EXIT_SUCCESS);
}

void	*ft_buffmove(char *buf, size_t start)
{
	size_t	i;

	i = 0;

	if (!buf || start >= ft_strlen(buf))
	{
		buf[0] = '\0';
		return (NULL);
	}

	while (buf[start])
	{
		buf[i] = buf[start];
		i++;
		start++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*ft_allocate_new_str(size_t s1_len, size_t len)
{
	char	*new_str;

	new_str = malloc(s1_len + len + 1);
	return (new_str);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s2_len;

	s2_len = ft_strlen(s2);
	if (len > s2_len)
		len = s2_len;
	new_str = ft_allocate_new_str(ft_strlen(s1), len);
	if (!new_str)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (free(s1), new_str);
}

static int	refill_buffer(int fd, char *buf, char **line)
{
	int	bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	buf[bytes_read] = '\0';
	return (bytes_read);
}

static int	buffer_initializer(int fd, char *buf, char **line)
{
	if (buf[0] == '\0')
	{
		return (refill_buffer(fd, buf, line));
	}
	else
	{
		return (1);
	}

}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			i;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);
	while (1)
	{
		bytes_read = buffer_initializer(fd, buf, &line);
		if (bytes_read <= 0)
			break ;
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		line = ft_strnjoin(line, buf, i + 1);
		if (!line)
			return (NULL);
		if (buf [i] == '\n')
			return (ft_buffmove(buf, i + 1), line);
		buf[0] = '\0';
	}
	return (line);
}

# include <stdio.h>
// TODO check if "read" values valid for moulinette
// Test with valgrind to make sure you are not leaking memory

int main()
{
	int fd = 0;

	fd = open("test.txt", O_RDONLY);
	// printf("%s\n", get_next_line(-1));
	//line = get_next_line(fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	printf("%s", get_next_line(fd));
	// while (line)
	// {
	// 	printf("%s\n", line);
	// 	line = get_next_line(fd);
	// }

	return 0;
}
