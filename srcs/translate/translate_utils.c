/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 21:42:06 by natakaha         ###   ########.fr       */
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
	return (axis);
}

double	detect_distance(double d1, double d2)
{
	double distance;
	
	distance = sqrt(d1 * d1 + d2 * d2);
	return (distance);
}

t_vec3	vec3_tlanslated(t_camera camera, t_input_state input)
{
	t_vec3	vector;
	t_vec3	rotate;
	t_vec3	axis;
	double	angle;

	axis = detect_axis(camera, input.input[T_UP], input.input[T_RIGHT]);
	angle = detect_distance(input.input[T_UP], input.input[T_RIGHT]) /
		WIN_W * camera.fov_deg / 180 * M_PI;
	vector = vec3_sub(interact_get_center(input.selected), camera.position);
	rotate = vec3_rodriges(vector, axis, angle);
	return (vec3_add(rotate, camera.position));	
}

t_vec3	vec3_forward(t_camera camera, t_input_state input, t_vec3 sub)
{
	double	distance_3d;
	double	distance_2d;
	double	forward_3d;
	t_vec3	forward;

	distance_3d = vec3_abs(sub);
	distance_2d = detect_distance(input.input[T_UP], input.input[T_RIGHT]);	
	if (distance_2d < EPS)
		return (ft_bzero(&forward, sizeof(t_vec3)), forward);
	forward_3d = distance_3d * input.input[T_FORWARD] / distance_2d;
	forward = vec3_scale(camera.forward, forward_3d);
	return (forward);
}
