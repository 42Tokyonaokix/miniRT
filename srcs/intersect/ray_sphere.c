/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 12:09:16 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

static t_vec3	ray_sphere_normal(t_sphere sphere, t_vec3 point);

t_hit	ray_sphere_hit(t_ray ray, t_sphere *sphere)
{
	double	t;
	t_hit	hit;
	
	t = ray_sphere_t(ray, *sphere);
	ft_bzero(&hit, sizeof(t_hit));
	if (t < 0)
		return (hit);
	hit.t = t;
	hit.point = ray_to_vec3(ray, t);
	hit.normal = ray_sphere_normal(*sphere, hit.point);
	hit.obj_type = OBJ_SPHERE;
	hit.obj_ptr = sphere;
	return (hit);
}

double	ray_sphere_t(t_ray ray, t_sphere sphere)
{
	t_vec3	const_v;
	double	quad_a;
	double	quad_b;
	double	quad_c;
	double	t;

	const_v = vec3_sub(ray.origin, sphere.center);
	quad_a = vec3_sq(ray.dir);
	quad_b = 2 * vec3_dot(const_v, ray.dir);
	quad_c = vec3_sq(const_v) - sphere.radius * sphere.radius;	
	t = quad_min_solution(quad_a, quad_b, quad_c);
	if (t < 0)
		return (ERRORNO);
	return (t);
}

static t_vec3	ray_sphere_normal(t_sphere sphere, t_vec3 point)
{
	t_vec3	vtmp;
	t_vec3	n;

	vtmp = vec3_sub(point, sphere.center);
	n = vec3_normalize(vtmp);
	return (n);
}

/* 
int	main(int argc, char **argv)
{
	t_ray		ray;
	t_sphere	sphere;
	t_hit		hit;

	if (argc != 11)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&sphere, sizeof(t_sphere));
	ray.origin.x = ft_atoi(argv[1]);
	ray.origin.y = ft_atoi(argv[2]);
	ray.origin.z = ft_atoi(argv[3]);
	vec3_print(ray.origin, "ray.origin");
	ray.dir.x = ft_atoi(argv[4]);
	ray.dir.y = ft_atoi(argv[5]);
	ray.dir.z = ft_atoi(argv[6]);
	ray.dir = vec3_normalize(ray.dir);
	vec3_print(ray.dir, "ray.dir");
	sphere.center.x = ft_atoi(argv[7]);
	sphere.center.y = ft_atoi(argv[8]);
	sphere.center.z = ft_atoi(argv[9]);
	vec3_print(sphere.center, "sphere.center");
	sphere.radius = ft_atoi(argv[10]);	
	hit = ray_sphere_hit(ray, &sphere);
	hit_print(hit, "hit");
} 
 */
