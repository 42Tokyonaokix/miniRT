/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 00:06:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int	app_init(t_app *app)
{
	if (mlx_ctx_init(&(app->render)) == NG)
		return (NG);
	error_message("app_init: mlx_ctx_init", "proceeded");
	if (camera_build_basis(&(app->scene.camera)) == NG)
		return (NG);
	return (OK);
}