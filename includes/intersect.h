/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/12 21:35:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "scene.h"

/* ========== Intersection Functions ========== */

int		intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *out);
int		intersect_plane(t_ray ray, t_plane *plane, t_hit *out);
int		intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *out);

/* ========== Find Closest Hit ========== */

int		find_closest_hit(const t_scene *scene, t_ray ray, t_hit *out);

#endif
