/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 19:49:09 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_color	render_exposed_color(t_hit hit, t_scene scene);
static t_color	render_shade_color(t_hit hit, t_scene scene);

bool	render_exposed_light(t_hit hit, t_light light, t_scene scene)
{
	t_ray	light_ray;
	t_hit	c_hit;
	t_vec3	v_tmp;

	light_ray.dir = vec3_sub(hit.point, light.position);
	if (vec3_sq(light_ray.dir) < EPS * EPS)
		return (false);
	light_ray.origin = light.position;
	c_hit = ray_closest_hit(light_ray, scene.spheres, scene.planes, scene.cylinders);
	v_tmp = vec3_sub(hit.point, c_hit.point);
	if (vec3_sq(v_tmp) < EPS * EPS)
		return (true);
	return (false);
}

t_color	render_detect_color(t_hit hit, t_scene scene)
{
	if (render_exposed_light(hit, scene.light, scene) == false)
		return (render_shade_color(hit, scene));
	else
		return (render_exposed_color(hit, scene));
}

static t_color	render_shade_color(t_hit hit, t_scene scene)
{
	t_ambient	amb;

	amb = scene.ambient;
	return (color_mul(hit.obj_color, color_scale(amb.color, amb.ratio)));
}

static t_color	render_exposed_color(t_hit hit, t_scene scene)
{
	t_color		c_dif;
	t_color		c_amb;
	t_light		light;
	double		l_scale;

	light = scene.light;
	c_amb = render_shade_color(hit, scene); 
	l_scale = vec3_dot(vec3_sub(light.position, hit.point), hit.normal) * light.ratio;
	if (l_scale < 0)
		l_scale = 0;
	c_dif = color_scale(color_mul(hit.obj_color, light.color), l_scale);
	return (color_add(c_amb, c_dif));
}
