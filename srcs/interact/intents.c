/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 18:04:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "app.h"

void	interact_space(t_app *app)
{
	(void)app;
	
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
