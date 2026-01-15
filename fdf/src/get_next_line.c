/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:03:18 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 18:42:05 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static char	*read_to_buffer(int fd, char *remainder, char *buffer);
static char	*update_remainder(char *line_buffer);
static char	*extract_line(char *remainder);

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remainder = read_to_buffer(fd, remainder, buffer);
	free(buffer);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = update_remainder(remainder);
	return (line);
}

static char	*read_to_buffer(int fd, char *rem, char *buf)
{
	ssize_t	bytes_read;

	if (rem && ft_strchr(rem, '\n'))
		return (rem);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		rem = ft_strjoin(rem, buf);
		if (!rem || ft_strchr(rem, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(rem);
		rem = NULL;
		return (NULL);
	}
	return (rem);
}

static char	*update_remainder(char *line_buffer)
{
	int		i;
	char	*new_remainder;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	if (!line_buffer[i])
	{
		free(line_buffer);
		return (NULL);
	}
	new_remainder = ft_strdup(line_buffer + i);
	free(line_buffer);
	return (new_remainder);
}

static char	*extract_line(char *remainder)
{
	int		i;
	char	*line;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i-- > 0)
		line[i] = remainder[i];
	return (line);
}
