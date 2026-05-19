/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/20 02:03:50 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

void	interact_space(t_app *app)
{
	(void)app;
	interact_next_selection(&app->scene, &app->input.selected);		
	logging_status("Space", "Space was pressed");
}

void	interact_enter(t_app *app)
{
	(void)app;
	
	logging_status("Enter", "Enter was pressed");
}

void	interact_tab(t_app *app)
{
	t_mode	*mode;

	mode = &(app->input.mode);
	if (*mode == TRANSLATE)
	{
		*mode = ROTATE;
		logging_status("mode chanded", "ROTATE MODE");
	}
	else
	{
		logging_status("mode chanded", "TRANSLATE MODE");
		*mode = TRANSLATE;
	}
}

void	interact_mouse_press(t_app *app, int x, int y)
{
	interact_pointer_obj(app, x, y);
	ft_dprintf(STDERR_FILENO, "mouse pressed x: %d, y: %d\n", x, y);

}

void	interact_mouse_release(t_app *app, int x, int y)
{
	ft_dprintf(STDERR_FILENO, "mouse released x: %d, y: %d\n", x, y);
	interact_pointer_diff(app, x, y);
	(void)app;
}
