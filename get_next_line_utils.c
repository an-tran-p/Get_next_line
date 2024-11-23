/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:59:24 by atran             #+#    #+#             */
/*   Updated: 2024/11/23 21:27:35 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen(s) + 1;
	dest = malloc(l * sizeof(char));
	if (!dest)
		return (0);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr;
	char		ch;

	ch = (char)c;
	ptr = s;
	while (*ptr != '\0' && *ptr != ch)
		ptr++;
	if (*ptr == ch || ch == '\0')
		return ((char *)ptr);
	else
		return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)d = *(unsigned char *)src;
		src++;
		d++;
		i++;
	}
	return (dest);
}
