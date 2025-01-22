/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <matskevich.ke@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:35 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/22 22:59:36 by kmatskev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <stdio.h>

size_t ft_strlen(const char *s)
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

int ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if(!dst || !src)
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
	size_t	j;

	i = 0;
	j = 0;
	while (buf[i] && i < start)
		i++;
	if (!buf[i])
	{
		buf[0] = '\0';
		return (NULL);
	}
	i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	return (buf);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	total_len;

	if (!s2)
	{
		return (NULL);
	}
	total_len = ft_strlen(s1) + (len + 1);
	new_str = malloc(total_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && j <= len)
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

char *get_next_line(int fd){
	char *line = NULL;
	static char buf[BUFFER_SIZE + 1];
	int buflen= 0;
	int i = 0;

	// check if "read" values valid for moulinette
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);

	// read from file descriptor
	while (1)
	{
		if (read(fd, buf, BUFFER_SIZE) < 0)
		{
			free(line);
			return (NULL);
		}
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (buf[i] == '\n' || (buf[i] == '\0'))
			{
				line = ft_strnjoin(line, buf, i);
				ft_buffmove(buf, i + 1);
				printf("buf: %s\n", buf);
				return (line);
			}
			i++;
		}
		line = ft_strnjoin(line, buf, BUFFER_SIZE);
		if (!line)
		{
			return (NULL);
		}
	}
// Test with valgrind to make sure you are not leaking memory
	return (line);
}

# include <stdio.h>


int main(int argc, char const *argv[])
{
	int fd = 0;
	char *line;

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
