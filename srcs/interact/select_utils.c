/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

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
