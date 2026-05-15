/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 00:35:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"

void	render_loop(t_app *app)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel_obj(&(app->render), app->scene, x, y);
			x++;
		}
		y++;
	}
}
