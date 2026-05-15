/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ctx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 22:25:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CTX_H
# define MLX_CTX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <mlx.h>
# include "app.h"
# include "parser.h"
# include "error.h"
# include "memory.h"

/* Forward declarations */
typedef struct s_app		t_app;
typedef struct s_render_ctx	t_render_ctx;

/* ========== MiniLibX Window & Image ========== */

int		mlx_ctx_init(t_render_ctx *ren);
void	setup_hooks(t_app *app);

/* ========== Rendering ========== */
void	render(t_app *app);
void	put_pixel_obj(t_render_ctx *ren, t_scene scene, int x, int y);
void	put_pixel_color(t_render_ctx *ren, int x, int y, int color);
int		pixel_detect_color(t_scene scene, int x, int y);

/* ========== Main Loop Functions ========== */
void	render_loop(t_app *app);

#endif
