/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 12:33:11 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

bool	if_valid_side_point(t_vec3 point, t_cylinder cyl)
{
	t_vec3	p_hor;
	t_vec3	c_hor;
	t_vec3	cord_p;
	double	half_h;

	half_h = cyl.height / 2;
	p_hor = vec3_hor(point, cyl.axis);
	c_hor = vec3_hor(cyl.center, cyl.axis);
	cord_p = vec3_sub(p_hor, c_hor);
	if (vec3_sq(cord_p) < half_h * half_h)
		return (true);
	return (false);
}

bool	if_valid_caps_point(t_vec3 point, t_cylinder cyl)
{
	t_vec3	p_ver;
	t_vec3	c_ver;
	t_vec3	cord_p;
	double	rad;

	rad = cyl.radius;
	p_ver = vec3_ver(point, cyl.axis);
	c_ver = vec3_ver(cyl.center, cyl.axis);
	cord_p = vec3_sub(p_ver, c_ver);
	if (vec3_sq(cord_p) < rad * rad)
		return (true);
	return (false);
}
