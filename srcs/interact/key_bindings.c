/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 18:02:49 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

static void	interact_key_press(int keycode, t_app *app);
static void	interact_key_release(int keycode, t_app *app);

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
		interact_key_press(keycode, app);
	else if (keycode == TAB)
		interact_tab(app);
	else if (keycode == SPACE)
		interact_space(app);
	else if (keycode == ENTER)
		interact_enter(app);
	return (0);
}

int	mlx_key_release(int keycode, void *param)
{
	t_app		*app;

	(void)keycode;
	app = (t_app *)param;
	if (keycode == W || keycode == S
		|| keycode == A || keycode == D
		|| keycode == E || keycode == Q
		|| keycode == LEFT_ARR || keycode == RIGHT_ARR
		|| keycode == UP_ARR || keycode == DOWN_ARR)
		interact_key_release(keycode, app);
	return (0);
}

static void	interact_key_press(int keycode, t_app *app)
{
	int	*start;

	start = app->input.start;
	if (keycode == W)
		time_press(&start[T_FORWARD]);
	else if (keycode == S)
		time_press(&start[T_BACK]);
	else if (keycode == A)
		time_press(&start[T_LEFT]);
	else if (keycode == D)
		time_press(&start[T_RIGHT]);
	else if (keycode == E)
		time_press(&start[T_DOWN]);
	else if (keycode == Q)
		time_press(&start[T_UP]);
	else if (keycode == LEFT_ARR)
		time_press(&start[R_LEFT]);
	else if (keycode == RIGHT_ARR)
		time_press(&start[R_RIGHT]);
	else if (keycode == UP_ARR)
		time_press(&start[R_UP]);
	else if (keycode == DOWN_ARR)
		time_press(&start[R_DOWN]);
	ft_dprintf(2, "%d was pressed\n", keycode);
}

static void	interact_key_release(int keycode, t_app *app)
{
	int	*start;
	int	*buf;

	start = app->input.start;
	buf = app->input.buf;
	if (keycode == W)
		time_release(&start[0], &buf[0]);
	else if (keycode == S)
		time_release(&start[1], &buf[1]);
	else if (keycode == A)
		time_release(&start[2], &buf[2]);
	else if (keycode == D)
		time_release(&start[3], &buf[3]);
	else if (keycode == E)
		time_release(&start[4], &buf[4]);
	else if (keycode == Q)
		time_release(&start[5], &buf[5]);
	else if (keycode == LEFT_ARR)
		time_release(&start[6], &buf[6]);
	else if (keycode == RIGHT_ARR)
		time_release(&start[7], &buf[7]);
	else if (keycode == UP_ARR)
		time_release(&start[8], &buf[8]);
	else if (keycode == DOWN_ARR)
		time_release(&start[9], &buf[9]);
	ft_dprintf(2, "%d was released\n", keycode);
}
