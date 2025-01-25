/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatskev <matskevich.ke@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:57:30 by kmatskev          #+#    #+#             */
/*   Updated: 2025/01/25 13:48:46 by kmatskev         ###   ########.fr       */
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

char	*ft_allocate_new_str(size_t s1_len, size_t len)
{
	char	*new_str;

	new_str = malloc(s1_len + len + 1);
	return (new_str);
}
