/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bindings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 17:53:32 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

int	mlx_mouse_press(void *param)
{
	t_app	*app;
	int		x;
	int		y;

	(void)param;
	app = (t_app *)param;
	mlx_mouse_get_pos(app->render.win, &x, &y);
	interact_mouse_press(app, x, y);
	return (0);
}

int	mlx_mouse_release(void *param)
{
	t_app	*app;
	int		x;
	int		y;

	(void)param;
	app = (t_app *)param;
	mlx_mouse_get_pos(app->render.win, &x, &y);
	interact_mouse_release(app, x, y);
	return (0);
}
