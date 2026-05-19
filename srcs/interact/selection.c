/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 19:13:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

t_select_kind	interact_print_selection(t_select_kind kind)
{
	if (kind == SEL_NONE)
		logging_status("NO OBJECTS", "was selected");
	if (kind == SEL_CAMERA)
		logging_status("CAMERA", "was selected");
	if (kind == SEL_LIGHT)
		logging_status("LIGHT", "was selected");
	if (kind == SEL_OBJECT)
		logging_status("OBJECT", "was selected");
	return (kind);
}

void	*interact_select_ptr(t_scene scene, t_select_kind kind)
{
	if (kind == SEL_NONE)
		return (NULL);
	if (kind == SEL_CAMERA)
		return (&scene.camera);
	if (kind == SEL_LIGHT)
		return (&scene.light);
	if (kind == SEL_OBJECT)
		return (NULL);
}

void	interact_valid_obj(t_scene scene, t_selection *current)
{
	if (current->obj_type == OBJ_SPHERE)
	{
		current->obj_type = OBJ_SPHERE;
		current->obj_ptr = scene.spheres;
	}
	if (current->obj_type == OBJ_SPHERE)
	{
		if (current->obj_ptr)
			return ;
		current->obj_type = OBJ_PLANE;
		current->obj_ptr = scene.planes;
	}
	if (current->obj_type == OBJ_PLANE)
	{
		if (current->obj_ptr)
			return ;
		current->obj_type = OBJ_CYLINDER;
		current->obj_ptr = scene.cylinders;
	}
	if (current->obj_ptr)
		return ;
	current->obj_type = OBJ_NONE;
	current->obj_ptr = NULL;
}

t_selection	interact_next_selection(t_scene scene, t_selection *current)
{
	if (current->kind == SEL_NONE)
	{
		current->kind = interact_print_selection(SEL_CAMERA);
		current->obj_ptr = interact_select_ptr(scene, current->kind);
	}
	else if (current->kind == SEL_CAMERA)
	{
		current->kind = interact_print_selection(SEL_LIGHT);
		current->obj_ptr = interact_select_ptr(scene, current->kind);
	}
	else if (current->kind == SEL_LIGHT)
	{
		current->kind = SEL_OBJECT;
		current->obj_type = SEL_NONE;
		current->obj_ptr = NULL;
	}
	if (current->kind == SEL_OBJECT)
	{
		
	}
}
