/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 23:16:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	put_pixel_obj(t_render_ctx *ren, t_scene scene, int x, int y)
{
	int	color;

	color = pixel_detect_color(scene, x, y);
	put_pixel_color(ren, x, y, color);
}

void	put_pixel_color(t_render_ctx *ren, int x, int y, int color)
{
	char	*pixel;

	pixel = ren->addr + y * ren->line_len + x * (ren->bpp / 8);
	*(unsigned int *)pixel = color;
}

int	pixel_detect_color(t_scene scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	int		color;

	ray = camera_pixel_ray(scene.camera, x, y);
	hit = ray_closest_hit(ray, scene.spheres, scene.planes, scene.cylinders);
	color = render_detect_color(hit, scene);
	return (color);
}
