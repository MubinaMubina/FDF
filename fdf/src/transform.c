/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:17 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 07:55:32 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

t_point	isometric_projection(t_point p)
{
	t_point	result;
	float	iso_x;
	float	iso_y;

	iso_x = (p.x - p.y) * cosf(M_PI / 6.0f);
	iso_y = (p.x + p.y) * sinf(M_PI / 6.0f) - p.z;
	result.x = iso_x;
	result.y = iso_y;
	result.z = p.z;
	return (result);
}

t_point	scale_point(t_point p, float zoom)
{
	t_point	result;

	result.x = p.x * zoom;
	result.y = p.y * zoom;
	result.z = p.z;
	return (result);
}

t_point	translate_point(t_point p, float tx, float ty)
{
	t_point	result;

	result.x = p.x + tx;
	result.y = p.y + ty;
	result.z = p.z;
	return (result);
}

void	rotation_placeholder(void)
{
	return ;
}