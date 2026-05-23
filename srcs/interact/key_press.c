/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 21:48:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"
#include "print.h"

static void	interact_space(t_app *app);
static void	interact_direct(int keycode, t_app *app);
static void	interact_enter(t_app *app);
static void	interact_preview(t_app *app);

int	mlx_key_press(int keycode, void *param)
{
	t_app				*app;

	(void)keycode;
	app = (t_app *)param;
	if (keycode == ESC)
		app_free(app);
	else if (keycode == W || keycode == S
		|| keycode == A || keycode == D
		|| keycode == E || keycode == Q
		|| keycode == LEFT_ARR || keycode == RIGHT_ARR
		|| keycode == UP_ARR || keycode == DOWN_ARR)
		interact_direct(keycode, app);
	else if (keycode == TAB)
		interact_preview(app);
	else if (keycode == SPACE)
		interact_space(app);
	else if (keycode == ENTER)
		interact_enter(app);
	return (0);
}

static void	interact_space(t_app *app)
{
	interact_next_selection(&app->scene, &app->input.selected);		
}

static void	interact_enter(t_app *app)
{
	if (app->input.selected.kind == SEL_NONE)
		return ;
	translate_motion(app->scene.camera, &app->input);
	interact_motion(&(app->input.selected), (app->input.move));
	print_motion_box(app->input, PRINT_APPLY);
	ft_bzero(&(app->input.move), sizeof(t_move));
	ft_bzero(&app->input.input, sizeof(int) * 5);
	render_loop(app);
	mlx_put_image_to_window(app->render.mlx, app->render.win,
		app->render.img, 0, 0);
}

static void	interact_preview(t_app *app)
{
	if (app->input.selected.kind == SEL_NONE)
		return ;
	translate_motion(app->scene.camera, &app->input);
	print_motion_box(app->input, PRINT_PREVIEW);
}

static void	interact_direct(int keycode, t_app *app)
{
	int	*input;

	input = app->input.input;
	if (keycode == W)
		input[T_FORWARD]++;
	else if (keycode == S)
		input[T_FORWARD]--;
	else if (keycode == A)
		input[T_RIGHT]--;
	else if (keycode == D)
		input[T_RIGHT]++;
	else if (keycode == E)
		input[T_UP]++;
	else if (keycode == Q)
		input[T_UP]--;
	else if (keycode == LEFT_ARR)
		input[R_RIGHT]--;
	else if (keycode == RIGHT_ARR)
		input[R_RIGHT]++;
	else if (keycode == UP_ARR)
		input[R_UP]++;
	else if (keycode == DOWN_ARR)
		input[R_UP]--;
}

// void	interact_mouse_press(t_app *app, int x, int y)
// {
// 	interact_pointer_obj(app, x, y);
// 	ft_dprintf(STDERR_FILENO, "mouse pressed x: %d, y: %d\n", x, y);

// }

// void	interact_mouse_release(t_app *app, int x, int y)
// {
// 	ft_dprintf(STDERR_FILENO, "mouse released x: %d, y: %d\n", x, y);
// 	interact_pointer_diff(app, x, y);
// 	(void)app;
// }
