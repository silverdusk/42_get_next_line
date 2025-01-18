/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <matskevich.ke@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:35 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/18 17:28:32 by kmatskev         ###   ########.fr       */
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


char *get_next_line(int fd){
	char *line;
	static char buf[BUFFER_SIZE + 1];
	int i = 0;

	// check if "read" values valid for moulinette
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);

	// read from file descriptor
	if (buf[0] == '\0')
	{
		read(fd, buf, BUFFER_SIZE);
		while (i < BUFFER_SIZE)
		{
			if (buf[i] == '\n')
			{
				line = malloc(sizeof(char) * i + 1);
				if (!line)
					return (NULL);
				ft_strncpy(line, buf, i);
				printf("%s\n", buf);
				ft_buffmove(buf, i);
				printf("%s\n", buf);
				return (line);
			}
			i++;
		}
	}
// TODO: check if buf is not empty
// Test with valgrind to make sure you are not leaking memory
	return (line);
}

# include <stdio.h>


int main(int argc, char const *argv[])
{
	int fd = 0;
	fd = open("test.txt", O_RDONLY);
	// printf("%s\n", get_next_line(-1));
	printf("%s\n", get_next_line(fd));

	return 0;
}
