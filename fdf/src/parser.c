/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:45:05 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/19 23:51:57 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
		if (!is_valid_number(split[x]))
		{
			free_split_safe(split);
			return (free(points), NULL);
		}
		points[x].x = (float)x;
		points[x].y = (float)y;
		points[x].z = (float)ft_atoi(split[x]);
		x++;
	}
	free_split_safe(split);
	return (points);
}

int	open_and_allocate(const char *filename, t_map *map)
{
	int	fd;

	map->height = count_height(filename);
	if (map->height <= 0)
		return (-1);
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map->points), -1);
	return (fd);
}

static void	cleanup_on_error(t_map *map, int y, char *line)
{
	while (--y >= 0)
		free(map->points[y]);
	free(map->points);
	map->points = NULL;
	free(line);
}

int	read_map_lines(int fd, t_map *map)
{
	int		y;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		if (y == 0)
			map->width = count_width(line);
		map->points[y] = parse_line(line, y, map->width);
		if (!map->points[y])
		{
			cleanup_on_error(map, y, line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	return (1);
}
