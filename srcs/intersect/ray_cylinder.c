/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 12:08:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

static t_vec3	cylinder_side_normal(t_vec3 point, t_cylinder cyl);
static t_vec3	cylinder_cap_normal(t_vec3 point, t_cylinder cyl);

t_hit	ray_cylinder_hit(t_ray ray, t_cylinder *cyl)
{
	double			t;
	t_point_type	type;
	t_hit			hit;

	ft_bzero(&hit, sizeof(t_hit));
	type = SIDE;
	t = ray_cylinder_t(ray, *cyl, &type);
	if (t < 0)
		return (hit);
	hit.t = t;
	hit.point = ray_to_vec3(ray, t);
	if (type == CAPS)
		hit.normal = cylinder_cap_normal(hit.point, *cyl);
	else
		hit.normal = cylinder_side_normal(hit.point, *cyl);
	hit.obj_type = OBJ_CYLINDER;
	hit.obj_ptr = cyl;
	return (hit);
}

static t_vec3	cylinder_side_normal(t_vec3 point, t_cylinder cyl)
{
	t_vec3	cord_p;
	t_vec3	normal;

	cord_p = vec3_sub(point, cyl.center);
	normal = vec3_ver(cord_p, cyl.axis);
	return (vec3_normalize(normal));
}

static t_vec3	cylinder_cap_normal(t_vec3 point, t_cylinder cyl)
{
	t_vec3	axis_n;
	t_vec3	to_p;

	axis_n = vec3_normalize(cyl.axis);
	to_p = vec3_sub(point, cyl.center);
	if (vec3_dot(to_p, cyl.axis) < 0)
		return (vec3_scale(axis_n, -1));
	return (axis_n);
}

/*
int	main(int argc, char **argv)
{
	t_ray		ray;
	t_cylinder	cylinder;
	t_hit		hit;
	t_point_type	type;
	double		t;

	if (argc != 15)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&cylinder, sizeof(t_cylinder));
	ray.origin.x = ft_atoi(argv[1]);
	ray.origin.y = ft_atoi(argv[2]);
	ray.origin.z = ft_atoi(argv[3]);
	vec3_print(ray.origin, "ray.origin");
	ray.dir.x = ft_atoi(argv[4]);
	ray.dir.y = ft_atoi(argv[5]);
	ray.dir.z = ft_atoi(argv[6]);
	ray.dir = vec3_normalize(ray.dir);
	vec3_print(ray.dir, "ray.dir");
	cylinder.center.x = ft_atoi(argv[7]);
	cylinder.center.y = ft_atoi(argv[8]);
	cylinder.center.z = ft_atoi(argv[9]);
	vec3_print(cylinder.center, "cylinder.center");
	cylinder.axis.x = ft_atoi(argv[10]);
	cylinder.axis.y = ft_atoi(argv[11]);
	cylinder.axis.z = ft_atoi(argv[12]);
	vec3_print(cylinder.axis, "cylinder.axis");
	cylinder.radius = ft_atoi(argv[13]);
	cylinder.height = ft_atoi(argv[14]);
	type = SIDE;
	t = ray_cylinder_t(ray, cylinder, &type);
	double_print(t, "t");
	hit = ray_cylinder_hit(ray, &cylinder);
	hit_print(hit, "hit");
}
*/
