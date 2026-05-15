/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 23:12:52 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 23:15:33 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	camera_half_w(t_camera camera)
{
	double	fov_rad;

	fov_rad = camera.fov_deg / 180 * M_PI;
	return (tan(fov_rad / 2));
}

double	camera_half_h(t_camera camera)
{
	double	half_w;

	half_w = camera_half_w(camera);
	return (half_w * WIN_H / WIN_W);
}
