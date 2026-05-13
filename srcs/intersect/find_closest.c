/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 18:06:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"

void	hit_print(t_hit hit, char *s)
{
	char	*type;
	
	printf("===\033[33mhit_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("point.x: %f\n", hit.point.x);
	printf("point.y: %f\n", hit.point.y);
	printf("point.z: %f\n", hit.point.z);
	printf("normal.x: %f\n", hit.normal.x);
	printf("normal.y: %f\n", hit.normal.y);
	printf("normal.z: %f\n", hit.normal.z);
	if (hit.obj_type == OBJ_CYLINDER)
		type = "OBJ_CYLINDER";
	if (hit.obj_type == OBJ_PLANE)
		type = "OBJ_PLANE";
	if (hit.obj_type == OBJ_SPHERE)
		type = "OBJ_SPHERE";
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
