/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 00:05:42 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"

/* linux */
// int	mlx_ctx_init(t_render_ctx *ren)
// {
// 	ren->mlx = mlx_init();
// 	if (ren->mlx == NULL)
// 		return (error_message("app_init: mlx_init", "failed"), NG);
// 	error_message("app_init: mlx_init", "proceeded");
// 	ren->win = mlx_new_window(ren->mlx, WIN_W, WIN_H, "miniRT");
// 	if (ren->win == NULL)
// 		return (error_message("app_init", "mlx_new_window failed"),
// 				mlx_destroy_display(ren->mlx), NG);
// 	error_message("app_init: mlx_new_window", "proceeded");
// 	ren->img = mlx_new_image(ren->mlx, WIN_W, WIN_H);
// 	if (ren->img == NULL)
// 		return (error_message("app_init", "mlx_new_img failed"),
// 			mlx_destroy_window(ren->mlx, ren->win),
// 		mlx_destroy_display(ren->mlx),
// 		NG);
// 	error_message("app_init: mlx_new_img", "proceeded");
// 	ren->addr = mlx_get_data_addr(ren->img, &ren->bpp, &ren->line_len, &ren->endian);
// 	if (ren->addr == NULL)
// 		return (error_message("app_init", "mlx_get_data_addr failed"),
// 			mlx_destroy_mem(ren), NG);
// 	return (OK);
// }

int	mlx_ctx_init(t_render_ctx *ren)
{
	ren->mlx = mlx_init();
	if (ren->mlx == NULL)
		return (error_message("app_init: mlx_init", "failed"), NG);
	error_message("app_init: mlx_init", "proceeded");
	ren->win = mlx_new_window(ren->mlx, WIN_W, WIN_H, "miniRT");
	if (ren->win == NULL)
		return (error_message("app_init", "mlx_new_window failed"), NG);
	error_message("app_init: mlx_new_window", "proceeded");
	ren->img = mlx_new_image(ren->mlx, WIN_W, WIN_H);
	if (ren->img == NULL)
		return (error_message("app_init", "mlx_new_img failed"),
			mlx_destroy_window(ren->mlx, ren->win), NG);
	error_message("app_init: mlx_new_img", "proceeded");
	ren->addr = mlx_get_data_addr(ren->img, &ren->bpp, &ren->line_len, &ren->endian);
	if (ren->addr == NULL)
		return (error_message("app_init", "mlx_get_data_addr failed"),
			mlx_destroy_mem(ren), NG);
	return (OK);
}
