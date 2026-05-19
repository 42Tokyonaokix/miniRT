/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 17:57:44 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"
#include "app.h"

int	mlx_event_hook(t_app *app)
{
	t_render_ctx	mlx;

	mlx = app->render;
	mlx_hook(mlx.win, 2, 1<<0, mlx_key_press, app);
	mlx_hook(mlx.win, 3, 1<<1, mlx_key_release, app);
	// mlx_hook(mlx.win, 4, 1<<2, mlx_mouse_press,app);
	// mlx_hook(mlx.win, 5, 1<<3, mlx_mouse_release,app);
	mlx_hook(mlx.win, 17, 0, (int (*)(void *))app_free, app);
	return (SUCCESS);
}
