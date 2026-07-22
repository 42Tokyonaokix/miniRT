/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/07/23 05:24:50 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"

void	mlx_destroy_mem(t_render_ctx *ren)
{
	mlx_destroy_image(ren->mlx, ren->img);
	mlx_destroy_window(ren->mlx, ren->win);
	mlx_destroy_display(ren->mlx);
	free(ren->mlx);
}
