/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rodrigues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/20 22:20:13 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_rodriges(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	v_rot;
	t_vec3	v_cos;
	t_vec3	k_dot;
	t_vec3	cross;

	v_cos = vec3_scale(v, cos(angle));
	k_dot = vec3_scale(axis, vec3_dot(v, axis) * (1 - cos(angle)));
	cross = vec3_scale(vec3_cross(axis, v), sin(angle));
	v_rot = vec3_add(v_cos, vec3_add(k_dot, cross));
	return (v_rot);
}
