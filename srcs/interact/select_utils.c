/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/20 01:38:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

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

void	interact_print_obj(t_obj_type type)
{
	if (type == OBJ_NONE)
		logging_status("NO OBJECTS", "was selected");
	if (type == OBJ_SPHERE)
		logging_status("OBJ-SPHERE", "was selected");
	if (type == OBJ_PLANE)
		logging_status("OBJ-PLANE", "was selected");
	if (type == OBJ_CYLINDER)
		logging_status("OBJ-CYLINDER", "was selected");
}

void	*interact_select_ptr(t_scene *scene, t_select_kind kind)
{
	if (kind == SEL_NONE)
		return (NULL);
	if (kind == SEL_CAMERA)
		return (&scene->camera);
	if (kind == SEL_LIGHT)
		return (&scene->light);
	if (kind == SEL_OBJECT)
		return (NULL);
	return (NULL);
}
