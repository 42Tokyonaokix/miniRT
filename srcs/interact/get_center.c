/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 04:39:22 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

t_vec3	interact_get_center(t_selection sel)
{
	t_vec3		v;

	if (sel.kind == SEL_CAMERA)
		return (((t_camera *)sel.obj_ptr)->position);
	if (sel.kind == SEL_LIGHT)
		return (((t_light *)sel.obj_ptr)->position);
	else if (sel.kind == SEL_OBJECT && sel.obj_type == OBJ_SPHERE)
		return (((t_sphere *)sel.obj_ptr)->center);
	else if (sel.kind == SEL_OBJECT && sel.obj_type == OBJ_PLANE)
		return (((t_plane *)sel.obj_ptr)->point);
	else if (sel.kind == SEL_OBJECT && sel.obj_type == OBJ_CYLINDER)
		return (((t_cylinder *)sel.obj_ptr)->center);
	return (ft_bzero(&v, sizeof(t_vec3)), v);
}
