/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/21 17:02:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

static void	interact_key_press(int keycode, t_app *app);

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

static void	interact_key_press(int keycode, t_app *app)
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
	ft_dprintf(2, "%d was pressed\n", keycode);
}
