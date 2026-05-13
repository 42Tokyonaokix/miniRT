/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 20:45:43 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"

t_hit	ray_cilinder_hit(t_ray ray, t_cylinder *cyl)
{
	double	t;
	t_hit	hit;

	ft_bzero(&hit, sizeof(t_hit));
	t = ray_cylinder_t(ray, *cyl);
	if (t < 0)
		return (hit);
	hit.point = ray_to_vec3(ray, t);
	hit.normal = 
}
