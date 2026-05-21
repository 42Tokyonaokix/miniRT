/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_trans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 17:12:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

static void	translate_rotation(t_camera camera, t_input_state input);
static void	translate_translation(t_camera camera, t_input_state input);

void	translate_motion(t_camera camera, t_input_state input)
{
	translate_rotation(camera, input);	
	translate_translation(camera, input);
}

static void	translate_rotation(t_camera camera, t_input_state input)
{
	double	distance;

	input.move.axis = detect_axis(camera, input);
	distance = detect_distance(input.input[R_UP], input.input[R_RIGHT]);	
	input.move.angle = distance * M_PI / WIN_H;
}

static void	translate_translation(t_camera camera, t_input_state input)
{
	t_vec3	sub;
	t_vec3	forward;

	sub = vec3_sub(vec3_tlanslated(camera, input),
		interact_get_center(input.selected));
	forward = vec3_forward(camera, input, sub);
	input.move.v_tls = vec3_add(sub, forward);
}
