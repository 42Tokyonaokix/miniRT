/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/23 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include <math.h>
#include <stdio.h>

static char	*selection_label(t_input_state input)
{
	if (input.selected.kind == SEL_NONE)
		return ("NONE");
	if (input.selected.kind == SEL_CAMERA)
		return ("CAMERA");
	if (input.selected.kind == SEL_LIGHT)
		return ("LIGHT");
	if (input.selected.obj_type == OBJ_SPHERE)
		return ("SPHERE");
	if (input.selected.obj_type == OBJ_PLANE)
		return ("PLANE");
	if (input.selected.obj_type == OBJ_CYLINDER)
		return ("CYLINDER");
	return ("OBJECT");
}

static char	*axis_label(t_vec3 axis)
{
	double	ax;
	double	ay;
	double	az;

	ax = fabs(axis.x);
	ay = fabs(axis.y);
	az = fabs(axis.z);
	if (ax >= ay && ax >= az)
		return ("x-axis");
	if (ay >= ax && ay >= az)
		return ("y-axis");
	return ("z-axis");
}

void	print_motion_box(t_input_state input, t_print_mode mode)
{
	double	angle_deg;

	angle_deg = input.move.angle * 180.0 / M_PI;
	dprintf(STDERR_FILENO,
		COL_BLUE "╔══════════════════════════════════════\n" COL_RESET);
	if (mode == PRINT_PREVIEW)
		dprintf(STDERR_FILENO,
			COL_BLUE "║" COL_RESET "  "
			COL_YELLOW COL_BOLD "▶ PREVIEW" COL_RESET "  "
			COL_DIM "TAB — no changes applied\n" COL_RESET);
	else
		dprintf(STDERR_FILENO,
			COL_BLUE "║" COL_RESET "  "
			COL_GREEN COL_BOLD "✔ APPLIED " COL_RESET "  "
			COL_DIM "ENTER — rendering...\n" COL_RESET);
	dprintf(STDERR_FILENO,
		COL_BLUE "╠══════════════════════════════════════\n" COL_RESET);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Selection" COL_RESET "  "
		COL_CYAN "%s\n" COL_RESET,
		selection_label(input));
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Input    " COL_RESET "  "
		"fwd" COL_BLUE " %d" COL_RESET
		"  up" COL_BLUE " %d" COL_RESET
		"  right" COL_BLUE " %d" COL_RESET
		"  rot_up" COL_BLUE " %d" COL_RESET
		"  rot_r" COL_BLUE " %d\n" COL_RESET,
		input.input[T_FORWARD], input.input[T_UP], input.input[T_RIGHT],
		input.input[R_UP], input.input[R_RIGHT]);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Rotate   " COL_RESET "  "
		COL_MAG "%s" COL_RESET "  "
		COL_BLUE "%.1f°\n" COL_RESET,
		axis_label(input.move.axis), angle_deg);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Translate" COL_RESET "  "
		COL_BLUE "(%.3f,  %.3f,  %.3f)\n" COL_RESET,
		input.move.v_tls.x, input.move.v_tls.y, input.move.v_tls.z);
	dprintf(STDERR_FILENO,
		COL_BLUE "╚══════════════════════════════════════\n" COL_RESET);
}
