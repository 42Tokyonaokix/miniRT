/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 11:48:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <mlx.h>
# include "app.h"

/* Forward declarations */
typedef struct s_app		t_app;
typedef struct s_render_ctx	t_render_ctx;

/* ========== MiniLibX Window & Image ========== */

int		app_init(t_app *app);
void	setup_hooks(t_app *app);

/* ========== Rendering ========== */

void	render(t_app *app);
void	put_pixel(t_render_ctx *render, int x, int y, int color);

/* ========== Main Loop Functions ========== */

int		on_render_loop(t_app *app);
int		on_destroy(t_app *app);

#endif
