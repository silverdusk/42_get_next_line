/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <kmatskev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:35 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/30 20:54:58 by kmatskev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	refill_buffer(int fd, char *buf, char **line)
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

int	buffer_initializer(int fd, char *buf, char **line)
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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			i;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX - 1)
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

/* # include <stdio.h>
// TODO check if "read" values valid for moulinette
// Test with valgrind to make sure you are not leaking memory

int main()
{
	int fd = 0;

	fd = open("test.txt", O_RDONLY);
	// printf("%s\n", get_next_line(-1));
	//line = get_next_line(fd);
	printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));

	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));

	// printf("%s", get_next_line(fd));
	// while (line)
	// {
	// 	printf("%s\n", line);
	// 	line = get_next_line(fd);
	// }

	return 0;
} */
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// A helper to read and print lines until NULL
void    read_and_print_all_lines(int fd)
{
    char *line;
    int  line_num = 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: \"%s\"\n", line_num++, line);
        free(line);
    }
}

void    test_with_file(const char *filename, const char *description)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    printf("=== %s ===\n", description);
    read_and_print_all_lines(fd);
    close(fd);
    printf("=== End of %s ===\n\n", description);
}

int main(void)
{
    // Test 1: multiple short lines
    test_with_file("test1.txt", "Test 1: multiple short lines");

    // Test 2: single long line (exceeds BUFFER_SIZE)
    test_with_file("test2.txt", "Test 2: single long line");

    // Test 3: empty file
    test_with_file("test3.txt", "Test 3: empty file");

    // Test 4: file with no newline
    test_with_file("test4.txt", "Test 4: no newline in file");

    // Test 5: file with only newlines
    test_with_file("test5.txt", "Test 5: file with only newlines");

    // Test 6: invalid file descriptor
    printf("=== Test 6: invalid file descriptor ===\n");
    int invalid_fd = -1;
    char *line = get_next_line(invalid_fd);
    if (!line)
        printf("As expected, get_next_line returned NULL for invalid fd.\n");
    else
    {
        printf("Unexpectedly got a line: %s\n", line);
        free(line);
    }
    printf("=== End of Test 6 ===\n\n");

    // printf("=== Test 7: reading from STDIN
	//		(type lines, press Ctrl+D to end) ===\n");
    // read_and_print_all_lines(STDIN_FILENO);
    // printf("=== End of Test 7 ===\n");

    return 0;
}*/
