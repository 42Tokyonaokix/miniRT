/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 by kesaitou                  #+#    #+#              */
/*   Updated: 2026/05/15 by kesaitou                 ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "scene.h"
#include "intersect.h"
#include <stdlib.h>

void	scene_free(t_scene *scene)
{
	t_sphere	*s_nxt;
	t_plane		*p_nxt;
	t_cylinder	*c_nxt;

	while (scene->spheres)
	{
		s_nxt = scene->spheres->next;
		free(scene->spheres);
		scene->spheres = s_nxt;
	}
	while (scene->planes)
	{
		p_nxt = scene->planes->next;
		free(scene->planes);
		scene->planes = p_nxt;
	}
	while (scene->cylinders)
	{
		c_nxt = scene->cylinders->next;
		free(scene->cylinders);
		scene->cylinders = c_nxt;
	}
}
