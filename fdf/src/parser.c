/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:45:05 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 14:34:07 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

int	count_width(char *line)
{
	int		count;
	char	**split;

	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	free_split_safe(split);
	return (count);
}

int	count_height(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

t_point	*parse_line(char *line, int y, int width)
{
	t_point	*points;
	char	**split;
	int		x;

	points = malloc(sizeof(t_point) * width);
	if (!points)
		return (NULL);
	split = ft_split(line, ' ');
	if (!split)
		return (free(points), NULL);
	x = 0;
	while (split[x] && x < width)
	{
		points[x].x = (float)x;
		points[x].y = (float)y;
		points[x].z = (float)ft_atoi(split[x]);
		x++;
	}
	free_split_safe(split);
	return (points);
}

t_map	parse_map(const char *filename)
{
	t_map map;
	int fd;
	int y;
	char *line;

	ft_memset(&map, 0, sizeof(t_map));
	map.height = count_height(filename);
	if (map.height <= 0)
		return (map);
	map.points = malloc(sizeof(t_point *) * map.height);
	if (!map.points)
		return (map);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map.points), map);
	y = 0;
	line = get_next_line(fd);
	while (line && y < map.height)
	{
		if (y == 0)
			map.width = count_width(line);
		map.points[y] = parse_line(line, y, map.width);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	return (map);
}
