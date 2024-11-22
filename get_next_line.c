/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:29:09 by atran             #+#    #+#             */
/*   Updated: 2024/11/22 16:56:28 by atran            ###   ########.fr       */
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
	l = ft_strlen((char *)s) + 1;
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

char	*ft_fill_line(char *src)
{
	char	*dest;
	size_t	size;
	size_t	i;

	i = 0;
	size = (ft_strchr(src, '\n') - src) + 1;
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_remain(char *s)
{
	char	*dest;
	char	*new_line;

	new_line = ft_strchr(s, '\n') + 1;
	if (*new_line == '\0')
	{
		ft_free(&s);
		return (NULL);
	}
	dest = ft_strdup(new_line);
	if (!dest)
	{
		ft_free(&s);
		return (NULL);
	}
	ft_free(&s);
	return (dest);
}
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_l;
	size_t	s2_l;
	char	*dest;

	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	dest = malloc((s1_l + s2_l + 1) * sizeof(char));
	if (!dest)
	{
		ft_free(&s1);
		return (NULL);
	}
	ft_memcpy(&dest[0], s1, s1_l);
	ft_memcpy(&dest[s1_l], s2, s2_l);
	dest[s1_l + s2_l] = '\0';
	ft_free(&s1);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!store)
		store = ft_strdup("");
	line = NULL;
	while (store)
	{
		if (ft_strchr(store, '\n') != NULL)
		{
			line = ft_fill_line(store);
			store = ft_remain(store);
			return (ft_free(&buffer), line);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0 && *store && ft_strchr(store, '\n') == NULL)
		{
			line = ft_strdup(store);
			return (ft_free(&buffer), ft_free(&store), line);
		}
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			store = ft_strjoin(store, buffer);
		}
		else
			return (ft_free(&buffer), NULL);
	}
	return (line);
}
