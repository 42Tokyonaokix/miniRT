/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/20 02:08:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"


void	interact_pointer_obj(t_app *app, int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = camera_pixel_ray(app->scene.camera, x, y);
	hit = ray_closest_hit(ray,
		app->scene.spheres, app->scene.planes, app->scene.cylinders);
	if (!hit.obj_ptr)
	{
		
	}
}