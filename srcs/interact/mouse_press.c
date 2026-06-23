/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 04:32:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

static t_selection	detect_pixel_selection(t_app *app, int x, int y);

void	mouse_left_press(t_app *app, int x, int y)
{
	app->input.selected = detect_pixel_selection(app, x, y);
	app->input.buf[T_RIGHT] = x;
	app->input.buf[T_UP] = y;
}

void	mouse_right_press(t_app *app, int x, int y)
{
	app->input.selected = detect_pixel_selection(app, x, y);
	app->input.buf[R_RIGHT] = x;
	app->input.buf[R_UP] = y;
}

static t_selection	detect_pixel_selection(t_app *app, int x, int y)
{
	t_ray		ray;
	t_hit		hit;
	t_selection	selected;

	ray = camera_pixel_ray(app->scene.camera, x, y);
	hit = ray_closest_hit(ray, app->scene.spheres,
			app->scene.planes, app->scene.cylinders);
	if (hit.obj_type == OBJ_NONE)
	{
		selected.kind = SEL_CAMERA;
		interact_print_selection(SEL_CAMERA);
		selected.obj_type = OBJ_NONE;
		selected.obj_ptr = &app->scene.camera;
		return (selected);
	}
	else
	{
		selected.kind = SEL_OBJECT;
		selected.obj_type = hit.obj_type;
		interact_print_obj(hit.obj_type);
		selected.obj_ptr = hit.obj_ptr;
	}
	return (selected);
}
