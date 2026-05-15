/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 14:47:14 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

void	hit_print(t_hit hit, char *s)
{
	char	*type;

	type = "UNKNOWN";
	if (hit.obj_type == OBJ_CYLINDER)
		type = "OBJ_CYLINDER";
	else if (hit.obj_type == OBJ_PLANE)
		type = "OBJ_PLANE";
	else if (hit.obj_type == OBJ_SPHERE)
		type = "OBJ_SPHERE";
	printf("===\033[33mhit_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("point.x: %f\n", hit.point.x);
	printf("point.y: %f\n", hit.point.y);
	printf("point.z: %f\n", hit.point.z);
	printf("normal.x: %f\n", hit.normal.x);
	printf("normal.y: %f\n", hit.normal.y);
	printf("normal.z: %f\n", hit.normal.z);
	printf("obj_type: %s\n", type);
	ft_putendl_fd("", 1);
}

t_vec3	ray_to_vec3(t_ray ray, double t)
{
	t_vec3	vtmp;
	t_vec3	v1;
	
	vtmp = vec3_scale(ray.dir, t);
	v1 = vec3_add(vtmp, ray.origin);
	return (v1);
}

static t_hit	hit_min(t_hit h_min, t_hit h_tmp)
{
	if (h_tmp.obj_type == OBJ_NONE)
		return (h_min);	
	else if (h_min.obj_type == OBJ_NONE)
		return (h_tmp);
	else if (h_min.t > h_tmp.t)
		return (h_tmp);
	return (h_min);
}

t_hit	ray_closest_hit(t_ray ray, t_sphere *sphere,
	t_plane *plane, t_cylinder *cylinder)
{
	t_hit	h_tmp;
	t_hit	h_min;
	
	ft_bzero(&h_tmp, sizeof(t_hit));
	ft_bzero(&h_min, sizeof(t_hit));
	while (sphere)
	{
		h_tmp = ray_sphere_hit(ray, sphere);
		h_min = hit_min(h_min, h_tmp);	
		sphere = sphere->next;
	}
	while (plane)
	{
		h_tmp = ray_plane_hit(ray, plane);
		h_min = hit_min(h_min, h_tmp);	
		plane = plane->next;
	}
	while (cylinder)
	{
		h_tmp = ray_cylinder_hit(ray, cylinder);
		h_min = hit_min(h_min, h_tmp);
		cylinder = cylinder->next;
	}
	return (h_min);
}
