/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_t.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"

static double	ray_cylinder_side_t(t_ray ray, t_cylinder cyl);
static double	ray_cyliner_top_t(t_ray ray, t_cylinder cyl);

t_hit	ray_cylinder_hit(t_ray ray, t_cylinder cyl)
{
	t_vec3	side_p;
	t_vec3	top_p;
	double	side_t;
	double	top_t;
	t_hit	hit;

	ft_bzero(&hit, sizeof(t_hit));
	side_t = ray_cylinder_side_t(ray, cyl);
	side_p = ray_to_vec3(ray, side_t);
	top_t = ray_cyliner_top_t(ray, cyl);
	top_p = ray_to_vec3(ray, ray_cyliner_top_t(ray, cyl));
	if (if_valid_side_point(side_p, cyl) == false)
		side_t = ERRORNO;
	if (if_valid_top_point(top_p, cyl) == false)
		top_t = ERRORNO;
	return (top_t);
}

static	bool	if_valid_side_point(t_vec3 point, t_cylinder cyl)
{
	t_vec3	p_hor;
	t_vec3	c_hor;
	t_vec3	cordinated_p;
	double	half_h;
	
	half_h = cyl.height / 2;
	p_hor = vec3_hor(point, cyl.axis);
	c_hor = vec3_hor(cyl.center, cyl.axis);
	cordinated_p = vec3_sub(p_hor, c_hor);
	if (vec3_sq(cordinated_p) < half_h * half_h)
		return (true);
	return (false);
}

static bool		if_valid_top_point(t_vec3 point, t_cylinder cyl)
{
	t_vec3	p_ver;
	t_vec3	c_ver;
	t_vec3	cordinated_p;
	double	rad;

	rad = cyl.radius;
	p_ver = vec3_ver(point, cyl.axis);
	c_ver = vec3_ver(cyl.center, cyl.axis);
	cordinated_p = vec3_sub(p_ver, c_ver);
	if (vec3_sq(cordinated_p) < rad * rad)
		return (true);
	return (false);
}

static double	ray_cylinder_side_t(t_ray ray, t_cylinder cyl)

{
	t_ray	ray_ver;
	double	quad_a;
	double	quad_b;
	double	quad_c;
	double	t;

	ray_ver.origin = vec3_ver(ray.origin, cyl.axis);
	ray_ver.dir = vec3_ver(ray.dir, cyl.axis);
	quad_a = vec3_sq(ray_ver.dir);
	quad_b = 2 * vec3_dot(ray_ver.origin, ray_ver.dir);
	quad_c = vec3_sq(ray_ver.origin) - cyl.radius * cyl.radius;
	t = quad_min_solutoin(quad_a, quad_b, quad_c);
	return (t);
}

static double	ray_cyliner_top_t(t_ray ray, t_cylinder cyl)
{
	t_plane	p1;
	t_plane	p2;
	t_vec3	v_top;
	double	t1;
	double	t2;

	ft_bzero(&p1, sizeof(t_plane));
	ft_bzero(&p2, sizeof(t_plane));
	p1.normal = cyl.axis;
	p2.normal = cyl.axis;
	v_top =  vec3_scale(cyl.axis, cyl.height / 2);
	p1.point = vec3_add(cyl.center,v_top);
	p2.point = vec3_sub(cyl.center, v_top);
	t1 = ray_plane_t(ray, p1);
	t2 = ray_plane_t(ray, p2);
	if (t1 < 0 && t2 < 0)
		return (ERRORNO);
	else if (t1 < 0)
		return (t2);
	else if (t2 < 0)
		return (t1);
	else if (t1 < t2)
		return (t1);
	return (t2);
}
