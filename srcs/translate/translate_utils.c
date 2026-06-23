/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 05:36:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

t_vec3	detect_axis(t_camera camera, int up, int right)
{
	t_vec3	axis_right;
	t_vec3	axis_up;
	t_vec3	axis;

	axis_right = vec3_scale(camera.right, up * -1);
	axis_up = vec3_scale(camera.up, right);
	axis = vec3_add(axis_right, axis_up);
	axis = vec3_normalize(axis);
	return (axis);
}

double	detect_distance(double d1, double d2)
{
	double	distance;

	distance = sqrt(d1 * d1 + d2 * d2);
	return (distance);
}

t_vec3	vec3_tlanslated(t_camera camera, t_input_state input)
{
	t_vec3	vector;
	t_vec3	axis;
	t_vec3	vr;
	t_vec3	vu;
	double	angle;

	axis = detect_axis(camera, input.input[T_UP], input.input[T_RIGHT]);
	angle = detect_distance(input.input[T_UP], input.input[T_RIGHT]);
	angle = angle * camera.fov_deg / WIN_W / 180 * M_PI;
	vector = vec3_sub(interact_get_center(input.selected), camera.position);
	vector = vec3_rodriges(vector, axis, angle);
	vector = vec3_add(vector, camera.position);
	vector = vec3_sub(vector, interact_get_center(input.selected));
	if (vec3_sq(vector) < EPS * EPS)
	{
		vr = vec3_scale(camera.right, input.input[T_RIGHT]);
		vu = vec3_scale(camera.up, input.input[T_UP]);
		vector = vec3_add(vr, vu);
	}
	return (vector);
}

t_vec3	vec3_forward(t_camera camera, t_input_state input)
{
	double	distance_xy;
	double	distance_z;
	t_vec3	vec3_forward;

	input.input[T_UP] = 0;
	input.input[T_RIGHT] = WIN_W;
	distance_xy = vec3_abs(vec3_tlanslated(camera, input));
	distance_z = distance_xy * input.input[T_FORWARD] / WIN_W;
	vec3_forward = vec3_scale(camera.forward, distance_z);
	return (vec3_forward);
}
