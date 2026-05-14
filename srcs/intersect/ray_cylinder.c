/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 08:55:49 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"

static t_vec3	cylinder_side_normal(t_vec3 point, t_cylinder cyl);

t_hit	ray_cylinder_hit(t_ray ray, t_cylinder *cyl)
{
	double		t;
	bool		point_is_top;
	t_hit		hit;

	ft_bzero(&hit, sizeof(t_hit));
	t = ray_cylinder_t(ray, *cyl);
	if (t < 0)
		return (hit);
	hit.point = ray_to_vec3(ray, t);
	point_is_top = if_valid_top_point(hit.point, *cyl);
	if (point_is_top == true)
		hit.normal = cyl->axis;
	else
		hit.normal = cylinder_side_normal(hit.point, *cyl);
	hit.obj_type = OBJ_CYLINDER;
	hit.obj_ptr = cyl;
	return (hit);
}

static t_vec3	cylinder_side_normal(t_vec3 point, t_cylinder cyl)
{
	t_vec3	cord_p;

	cord_p = vec3_sub(point, cyl.center);
	return (vec3_ver(cord_p, cyl.axis));
}



int	main(int argc, char **argv)
{
	t_ray		ray;
	t_cylinder	cylinder;
	t_hit		hit;
	double		t;

	if (argc != 15)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&cylinder, sizeof(t_plane));
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
	t = ray_cylinder_t(ray, cylinder);
	double_print(t, "t");
	hit = ray_cylinder_hit(ray, &cylinder);
	hit_print(hit, "hit");
} 


