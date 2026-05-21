/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bindings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 04:21:07 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

static void	interact_mouse_press(t_app *app, int button, int x, int y);
static void	interact_mouse_release(t_app *app, int button, int x, int y);

int	mlx_mouse_press(int button, int x, int y, void *param)
{
	t_app			*app;
	t_render_ctx	render;

	app = (t_app *)param;
	render = app->render;
	interact_mouse_press(app, button, x, y);
	return (0);
}

int	mlx_mouse_release(int button, int x, int y, void *param)
{
	t_app			*app;
	t_render_ctx	render;

	app = (t_app *)param;
	render = app->render;
	interact_mouse_release(app, button, x, y);
	return (0);
}

static void	interact_mouse_press(t_app *app, int button, int x, int y)
{
	if (button == LEFT)
		mouse_left_press(app, x, y);
	if (button == RIGHT)
		mouse_right_press(app, x, y);
}

static void	interact_mouse_release(t_app *app, int button, int x, int y)
{
	if (button == LEFT)
		mouse_left_release(app, x, y);
	if (button == RIGHT)
		mouse_right_release(app, x, y);
}
