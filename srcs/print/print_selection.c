/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_selection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/23 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "print.h"

t_select_kind	interact_print_selection(t_select_kind kind)
{
	if (kind == SEL_NONE)
		logging_sel("NONE", "selected");
	else if (kind == SEL_CAMERA)
		logging_sel("CAMERA", "selected");
	else if (kind == SEL_LIGHT)
		logging_sel("LIGHT", "selected");
	else if (kind == SEL_OBJECT)
		logging_sel("OBJECT", "selected");
	return (kind);
}

void	interact_print_obj(t_obj_type type)
{
	if (type == OBJ_NONE)
		logging_sel("OBJ-NONE", "selected");
	else if (type == OBJ_SPHERE)
		logging_sel("OBJ-SPHERE", "selected");
	else if (type == OBJ_PLANE)
		logging_sel("OBJ-PLANE", "selected");
	else if (type == OBJ_CYLINDER)
		logging_sel("OBJ-CYLINDER", "selected");
}
