/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_t.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 12:33:11 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

static double	ray_cylinder_side_t(t_ray ray, t_cylinder cyl);
static double	ray_cylinder_caps_t(t_ray ray, t_cylinder cyl);

double	ray_cylinder_t(t_ray ray, t_cylinder cyl, t_point_type *type)
{
	double	side_t;
	double	caps_t;
	double	min_t;
	t_vec3	p;

	side_t = ray_cylinder_side_t(ray, cyl);
	if (side_t >= 0)
	{
		p = ray_to_vec3(ray, side_t);
		if (if_valid_side_point(p, cyl) == false)
			side_t = ERRORNO;
	}
	caps_t = ray_cylinder_caps_t(ray, cyl);
	if (caps_t >= 0)
	{
		p = ray_to_vec3(ray, caps_t);
		if (if_valid_caps_point(p, cyl) == false)
			caps_t = ERRORNO;
	}
	min_t = min_double(side_t, caps_t);
	if (min_t == caps_t)
		*type = CAPS;
	if (min_t == side_t)
		*type = SIDE;
	return (min_t);
}

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

/*
** Returns only the nearer root of the side quadratic. When that root lies
** outside the cylinder's height range, ray_cylinder_caps_t catches the
** ray on the cap it must have crossed first, so the visible surface stays
** correct without testing the farther root explicitly.
*/
static double	ray_cylinder_side_t(t_ray ray, t_cylinder cyl)
{
	t_vec3	offset;
	t_ray	ray_ver;
	double	quad_a;
	double	quad_b;
	double	quad_c;

	offset = vec3_sub(ray.origin, cyl.center);
	ray_ver.origin = vec3_ver(offset, cyl.axis);
	ray_ver.dir = vec3_ver(ray.dir, cyl.axis);
	quad_a = vec3_sq(ray_ver.dir);
	quad_b = 2 * vec3_dot(ray_ver.origin, ray_ver.dir);
	quad_c = vec3_sq(ray_ver.origin) - cyl.radius * cyl.radius;
	return (quad_min_solution(quad_a, quad_b, quad_c));
}

static double	ray_cylinder_caps_t(t_ray ray, t_cylinder cyl)
{
	t_plane	p1;
	t_plane	p2;
	t_vec3	v_caps;
	double	t1;
	double	t2;

	ft_bzero(&p1, sizeof(t_plane));
	ft_bzero(&p2, sizeof(t_plane));
	p1.normal = cyl.axis;
	p2.normal = cyl.axis;
	v_caps = vec3_scale(cyl.axis, cyl.height / 2);
	p1.point = vec3_add(cyl.center, v_caps);
	p2.point = vec3_sub(cyl.center, v_caps);
	t1 = ray_plane_t(ray, p1);
	t2 = ray_plane_t(ray, p2);
	return (min_double(t1, t2));
}
