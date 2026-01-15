/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:17 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 21:00:03 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	isometric(float *x, float *y, float z)
{
	float	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z;
}

/* Rotate point around X-axis by angle (in radians) */
static void	rotate_x(float *y, float *z, float angle)
{
	float	tmp_y;

	tmp_y = *y;
	*y = tmp_y * cos(angle) - *z * sin(angle);
	*z = tmp_y * sin(angle) + *z * cos(angle);
}

/* Rotate point around Y-axis by angle (in radians) */
static void	rotate_y(float *x, float *z, float angle)
{
	float	tmp_x;

	tmp_x = *x;
	*x = tmp_x * cos(angle) + *z * sin(angle);
	*z = -tmp_x * sin(angle) + *z * cos(angle);
}

/* Rotate point around Z-axis by angle (in radians) */
static void	rotate_z(float *x, float *y, float angle)
{
	float	tmp_x;

	tmp_x = *x;
	*x = tmp_x * cos(angle) - *y * sin(angle);
	*y = tmp_x * sin(angle) + *y * cos(angle);
}

/*
** Project a 3D point to 2D based on camera type.
** ISOMETRIC: uses fixed 30-degree isometric projection.
** PARALLEL: applies rotation matrices using cam.angle_x/y/z
**           - Key 1: top-down view (no rotation)
**           - Key 2: front view (90° X rotation)
**           - Key 3: side view (90° Y and -90° Z rotation)
*/
t_point	project_point(t_point p, t_fdf *fdf)
{
	t_point	res;

	res = p;
	if (fdf->cam.type == ISOMETRIC)
		isometric(&res.x, &res.y, res.z);
	else if (fdf->cam.type == PARALLEL)
	{
		rotate_x(&res.y, &res.z, fdf->cam.angle_x);
		rotate_y(&res.x, &res.z, fdf->cam.angle_y);
		rotate_z(&res.x, &res.y, fdf->cam.angle_z);
	}
	return (res);
}
