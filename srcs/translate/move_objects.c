/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 01:55:46 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

void	move_sphere(t_sphere *sphere, t_move move)
{
	sphere->center = vec3_add(sphere->center, move.v_tls);	
}

void	move_plane(t_plane *plane, t_move move)
{
	plane->point = vec3_add(plane->point, move.v_tls);
	plane->normal = vec3_rodriges(plane->normal, move.axis, move.angle);	
}

void	move_cylinder(t_cylinder *cylinder, t_move move)
{
	cylinder->center = vec3_add(cylinder->center, move.v_tls);
	cylinder->axis = vec3_rodriges(cylinder->axis, move.axis, move.angle);
}

void	move_camera(t_camera *camera, t_move move)
{
	camera->position = vec3_add(camera->position, move.v_tls);
	move.axis = vec3_scale(move.axis, -1);
	camera->forward = vec3_rodriges(camera->forward, move.axis, move.angle);
	camera->up = vec3_rodriges(camera->up, move.axis, move.angle);
	camera->right = vec3_rodriges(camera->right, move.axis, move.angle);
}

void	move_light(t_light *light, t_move move)
{
	light->position = vec3_add(light->position, move.v_tls);
}
