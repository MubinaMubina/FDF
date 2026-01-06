/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:17 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 16:45:53 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

t_point	isometric_projection(t_point p)
{
	t_point	res;
	float	prev_x;
	float	prev_y;

	prev_x = p.x;
	prev_y = p.y;
	res.x = (prev_x - prev_y) * cos(0.523599); // cos(30 degrees)
	res.y = (prev_x + prev_y) * sin(0.523599) - p.z;
	res.z = p.z;
	return (res);
}


t_point	scale_point(t_point p, float zoom)
{
	t_point	result;

	result.x = p.x * zoom;
	result.y = p.y * zoom;
	result.z = p.z;
	return (result);
}

t_point	translate_point(t_point p, float offset_x, float offset_y)
{
	p.x += offset_x;
	p.y += offset_y;
	return (p);
}

void	rotation_placeholder(void)
{
	return ;
}
