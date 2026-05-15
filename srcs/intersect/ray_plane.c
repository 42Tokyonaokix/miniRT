/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 15:26:10 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

t_hit	ray_plane_hit(t_ray ray, t_plane *plane)
{
	double	t;
	t_hit	hit;

	t = ray_plane_t(ray, *plane);
	ft_bzero(&hit, sizeof(t_hit));
	if (t < 0)
		return (hit);
	hit.t = t;
	hit.point = ray_to_vec3(ray, t);
	hit.normal = plane->normal;
	hit.obj_type = OBJ_PLANE;
	hit.obj_ptr = plane;
	hit.obj_color = plane->color;
	return (hit);
}

double	ray_plane_t(t_ray ray, t_plane plane)
{
	t_vec3	const_v;
	double	const_n;
	double	varia_n;
	double	t;

	const_v = vec3_sub(ray.origin, plane.point);
	const_n = vec3_dot(const_v, plane.normal);
	varia_n = vec3_dot(ray.dir, plane.normal);
	if (varia_n * varia_n < EPS * EPS)
		return (ERRORNO);
	t = -(const_n / varia_n);
	if (t < EPS)
		return (ERRORNO);
	return (t);
}

/*
int	main(int argc, char **argv)
{
	t_ray	ray;
	t_plane	plane;
	t_hit	hit;

	if (argc != 13)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&plane, sizeof(t_plane));
	ray.origin.x = ft_atoi(argv[1]);
	ray.origin.y = ft_atoi(argv[2]);
	ray.origin.z = ft_atoi(argv[3]);
	vec3_print(ray.origin, "ray.origin");
	ray.dir.x = ft_atoi(argv[4]);
	ray.dir.y = ft_atoi(argv[5]);
	ray.dir.z = ft_atoi(argv[6]);
	ray.dir = vec3_normalize(ray.dir);
	vec3_print(ray.dir, "ray.dir");
	plane.point.x = ft_atoi(argv[7]);
	plane.point.y = ft_atoi(argv[8]);
	plane.point.z = ft_atoi(argv[9]);
	vec3_print(plane.point, "plane.point");
	plane.normal.x = ft_atoi(argv[10]);
	plane.normal.y = ft_atoi(argv[11]);
	plane.normal.z = ft_atoi(argv[12]);
	plane.normal = vec3_normalize(plane.normal);
	vec3_print(plane.normal, "plane.normal");
	hit = ray_plane_hit(ray, &plane);
	hit_print(hit, "hit");
} 
*/
