/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_apply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 19:14:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

void	interact_motion(t_selection *sel, t_move move)
{
	if (sel->kind == SEL_NONE)
		return ;
	else if (sel->kind == SEL_CAMERA)
		move_camera(sel->obj_ptr, move);
	else if (sel->kind == SEL_LIGHT)
		move_light(sel->obj_ptr, move);
	else if (sel->kind == SEL_OBJECT && sel->obj_type == OBJ_SPHERE)	
		move_sphere(sel->obj_ptr, move);
	else if (sel->kind == SEL_OBJECT && sel->obj_type == OBJ_PLANE)
		move_plane(sel->obj_ptr, move);
	else if (sel->kind == SEL_OBJECT && sel->obj_type == OBJ_CYLINDER)
		move_cylinder(sel->obj_ptr, move);
	return ;
}

void	interact_move(t_selection *sel, t_move *move)
{
	interact_motion(sel, *move);
	ft_bzero(move, sizeof(t_move));
	return ;
}
