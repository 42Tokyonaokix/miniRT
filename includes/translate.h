/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 20:20:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 03:33:55 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATE_H
# define TRANSLATE_H

# include "interact.h"

/* ========== Translation Functions ========== */
t_vec3		detect_axis(t_camera camera, int up, int right);
double		detect_distance(double d1, double d2);
t_vec3		vec3_tlanslated(t_camera camera, t_input_state input);
t_vec3		vec3_forward(t_camera camera, t_input_state input);
void		translate_motion(t_camera camera, t_input_state *input);
void		move_sphere(t_sphere *sphere, t_move move);
void		move_plane(t_plane *plane, t_move move);
void		move_cylinder(t_cylinder *cylinder, t_move move);
void		move_camera(t_camera *camera, t_move move);
void		move_light(t_light *light, t_move move);
void		interact_motion(t_selection *sel, t_move move);
t_vec3		interact_get_center(t_selection sel);
void		print_motion(t_input_state input);

#endif