/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_release.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 04:33:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

void	mouse_left_release(t_app *app, int x, int y)
{
	if (app->input.selected.kind == SEL_NONE)
		return ;
	app->input.input[T_RIGHT] = -(x - app->input.buf[T_RIGHT]);
	app->input.input[T_UP] = y - app->input.buf[T_UP];
	translate_motion(app->scene.camera, &app->input);
	print_motion(app->input);
	interact_motion(&(app->input.selected), (app->input.move));
	ft_bzero(&(app->input.move), sizeof(t_move));
	ft_bzero(&app->input.input, sizeof(int) * 5);
	ft_bzero(&app->input.buf, sizeof(int) * 5);
	render_loop(app);
	mlx_put_image_to_window(app->render.mlx,
		app->render.win,app->render.img, 0, 0);	
}

void	mouse_right_release(t_app *app, int x, int y)
{	
	if (app->input.selected.kind == SEL_NONE)
		return ;
	app->input.input[R_RIGHT] = x - app->input.buf[R_RIGHT];
	app->input.input[R_UP] = y - app->input.buf[R_UP];
	translate_motion(app->scene.camera, &app->input);
	interact_motion(&(app->input.selected), (app->input.move));
	print_motion(app->input);
	ft_bzero(&(app->input.move), sizeof(t_move));
	ft_bzero(&app->input.input, sizeof(int) * 5);
	ft_bzero(&app->input.buf, sizeof(int) * 5);
	render_loop(app);
	mlx_put_image_to_window(app->render.mlx,
		app->render.win,app->render.img, 0, 0);	
}