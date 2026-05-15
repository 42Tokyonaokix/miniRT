/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 00:05:23 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"

void	mlx_destroy_mem(t_render_ctx *ren)
{
	mlx_destroy_image(ren->mlx, ren->img);
	mlx_destroy_window(ren->mlx, ren->win);
	// mlx_destroy_display(ren->mlx);
}