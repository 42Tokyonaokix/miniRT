/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 19:38:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

static void	interact_valid_obj(t_scene *scene, t_selection *current);
static void	interact_next_obj(t_scene *scene, t_selection *current);

void	interact_next_selection(t_scene *scene, t_selection *current)
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
		current->obj_type = OBJ_NONE;
		current->obj_ptr = NULL;
	}
	if (current->kind == SEL_OBJECT)
	{
		interact_next_obj(scene, current);
		interact_print_obj(current->obj_type);			
	}
}

static void	interact_valid_obj(t_scene *scene, t_selection *current)
{
	if (current->obj_type == OBJ_NONE)
	{
		current->obj_type = OBJ_SPHERE;
		current->obj_ptr = scene->spheres;
	}
	if (current->obj_type == OBJ_SPHERE)
	{
		if (current->obj_ptr)
			return ;
		current->obj_type = OBJ_PLANE;
		current->obj_ptr = scene->planes;
	}
	if (current->obj_type == OBJ_PLANE)
	{
		if (current->obj_ptr)
			return ;
		current->obj_type = OBJ_CYLINDER;
		current->obj_ptr = scene->cylinders;
	}
	if (current->obj_ptr)
		return ;
	current->obj_type = OBJ_NONE;
	current->kind = SEL_NONE;
	current->obj_ptr = NULL;
}

static void	interact_next_obj(t_scene *scene, t_selection *current)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	
	if (current->obj_type == OBJ_NONE)
		interact_valid_obj(scene, current);
	else if (current->obj_type == OBJ_SPHERE)
	{
		sphere = current->obj_ptr;
		current->obj_ptr = sphere->next;
		interact_valid_obj(scene, current);
	}
	else if (current->obj_type == OBJ_PLANE)
	{
		plane = current->obj_ptr;
		current->obj_ptr = plane->next;
		interact_valid_obj(scene, current);
	}
	else if (current->obj_type == OBJ_CYLINDER)
	{
		cylinder = current->obj_ptr;
		current->obj_ptr = cylinder->next;
		interact_valid_obj(scene, current);
	}
}
