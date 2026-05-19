/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/20 01:11:12 by natakaha         ###   ########.fr       */
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
	int	*k_start;

	k_start = app->input.k_start;
	if (keycode == W)
		time_press(&k_start[T_FORWARD]);
	else if (keycode == S)
		time_press(&k_start[T_BACK]);
	else if (keycode == A)
		time_press(&k_start[T_LEFT]);
	else if (keycode == D)
		time_press(&k_start[T_RIGHT]);
	else if (keycode == E)
		time_press(&k_start[T_DOWN]);
	else if (keycode == Q)
		time_press(&k_start[T_UP]);
	else if (keycode == LEFT_ARR)
		time_press(&k_start[R_LEFT]);
	else if (keycode == RIGHT_ARR)
		time_press(&k_start[R_RIGHT]);
	else if (keycode == UP_ARR)
		time_press(&k_start[R_UP]);
	else if (keycode == DOWN_ARR)
		time_press(&k_start[R_DOWN]);
	ft_dprintf(2, "%d was pressed\n", keycode);
}

static void	interact_key_release(int keycode, t_app *app)
{
	int	*k_start;
	int	*k_buf;

	k_start = app->input.k_start;
	k_buf = app->input.k_buf;
	if (keycode == W)
		time_release(&k_start[0], &k_buf[0]);
	else if (keycode == S)
		time_release(&k_start[1], &k_buf[1]);
	else if (keycode == A)
		time_release(&k_start[2], &k_buf[2]);
	else if (keycode == D)
		time_release(&k_start[3], &k_buf[3]);
	else if (keycode == E)
		time_release(&k_start[4], &k_buf[4]);
	else if (keycode == Q)
		time_release(&k_start[5], &k_buf[5]);
	else if (keycode == LEFT_ARR)
		time_release(&k_start[6], &k_buf[6]);
	else if (keycode == RIGHT_ARR)
		time_release(&k_start[7], &k_buf[7]);
	else if (keycode == UP_ARR)
		time_release(&k_start[8], &k_buf[8]);
	else if (keycode == DOWN_ARR)
		time_release(&k_start[9], &k_buf[9]);
	ft_dprintf(2, "%d was released\n", keycode);
}
