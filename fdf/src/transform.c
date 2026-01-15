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

// #include "../include/fdf.h"

// void	rotate_x(float *y, float *z, double angle)
// {
// 	float	prev_y;

// 	prev_y = *y;
// 	*y = prev_y * cos(angle) + *z * sin(angle);
// 	*z = -prev_y * sin(angle) + *z * cos(angle);
// }

// void	rotate_y(float *x, float *z, double angle)
// {
// 	float	prev_x;

// 	prev_x = *x;
// 	*x = prev_x * cos(angle) + *z * sin(angle);
// 	*z = -prev_x * sin(angle) + *z * cos(angle);
// }

// void	rotate_z(float *x, float *y, double angle)
// {
// 	float	prev_x;

// 	prev_x = *x;
// 	*x = prev_x * cos(angle) - *y * sin(angle);
// 	*y = prev_x * sin(angle) + *y * cos(angle);
// }

// t_point	project_point(t_point p, t_fdf *fdf)
// {
// 	float	prev_x;
// 	float	prev_y;

// 	rotate_x(&p.y, &p.z, fdf->cam.angle_x);
// 	rotate_y(&p.x, &p.z, fdf->cam.angle_y);
// 	rotate_z(&p.x, &p.y, fdf->cam.angle_z);
// 	if (fdf->cam.type == ISOMETRIC)
// 	{
// 		prev_x = p.x;
// 		prev_y = p.y;
// 		p.x = (prev_x - prev_y) * cos(0.523599);
// 		p.y = (prev_x + prev_y) * sin(0.523599) - p.z;
// 	}
// 	return (p);
// }
#include "../include/fdf.h"

void	isometric(float *x, float *y, float z)
{
	float	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z;
}

// t_point	project_point(t_point p, t_fdf *fdf)
// {
// 	t_point	res;

// 	res.x = p.x;
// 	res.y = p.y;
// 	res.z = p.z;
// 	if (fdf->cam.type == ISOMETRIC)
// 	{
// 		isometric(&res.x, &res.y, res.z);
// 	}
// 	return (res);
// }

// #include "../include/fdf.h"
// #include <math.h>

// void	isometric(float *x, float *y, float z)
// {
// 	float	prev_x;
// 	float	prev_y;

// 	prev_x = *x;
// 	prev_y = *y;
// 	// 0.523599 radians = 30 degrees
// 	*x = (prev_x - prev_y) * cos(0.523599);
// 	*y = (prev_x + prev_y) * sin(0.523599) - z;
// }

t_point	project_point(t_point p, t_fdf *fdf)
{
	t_point	res;

	res = p;
	if (fdf->cam.type == ISOMETRIC)
		isometric(&res.x, &res.y, res.z);
	// Note: If you have rotation functions, apply them before isometric()
	return (res);
}
