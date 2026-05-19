/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/19 20:35:07 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int	app_init(t_app *app)
{
	if (mlx_ctx_init(&(app->render)) == FAILURE)
		return (FAILURE);
	logging_status("app_init: mlx_ctx_init", "proceeded");
	if (camera_build_basis(&(app->scene.camera)) == FAILURE)
		return (FAILURE);
	logging_status("app_init: camera_build_basis", "proceeded");
	if (mlx_event_hook(app) == FAILURE)
		return (FAILURE);
	logging_status("app_init: event hooks", "preceeded");
	return (SUCCESS);
}
