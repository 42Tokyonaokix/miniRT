/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 03:43:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

static void	translate_rotation(t_camera camera, t_input_state *input);
static void	translate_translation(t_camera camera, t_input_state *input);

void	translate_motion(t_camera camera, t_input_state *input)
{
	translate_rotation(camera, input);
	translate_translation(camera, input);
}

static void	translate_rotation(t_camera camera, t_input_state *input)
{
	double	distance;

	input->move.axis = (detect_axis(camera,
			input->input[R_UP], input->input[R_RIGHT]));
	distance = detect_distance(input->input[R_UP], input->input[R_RIGHT]);
	input->move.angle = distance * M_PI / WIN_H * 10;
}

static void	translate_translation(t_camera camera, t_input_state *input)
{
	t_vec3	delta;
		
	delta = vec3_add(vec3_tlanslated(camera, *input), vec3_forward(camera, *input));
	input->move.v_tls = delta;
}

void	print_motion(t_input_state input)
{
	t_select_kind kind;
	
	ft_dprintf(STDERR_FILENO, "======%s======\n", "Enter was pressed.");
	kind = interact_print_selection(input.selected.kind);
	if (kind == SEL_OBJECT)
		interact_print_obj(input.selected.obj_type);
	ft_dprintf(STDERR_FILENO, "\n print_input\n");
	ft_dprintf(STDERR_FILENO, "T_FORWARD : %d,  T_UP : %d, T_RIGHT : %d\n",
		input.input[T_FORWARD], input.input[T_UP], input.input[T_RIGHT]);
	ft_dprintf(STDERR_FILENO, "R_RIGHT : %d,  R_UP : %d\n",
		input.input[R_UP], input.input[R_RIGHT]);
	ft_dprintf(STDERR_FILENO, "\n\n print_move\n");
	vec3_print(input.move.axis, "rotate_axis");
	double_print(input.move.angle, "rotate_angle");
	vec3_print(input.move.v_tls, "translate");	
}
