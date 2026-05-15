/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 23:24:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "render.h"
# include "mlx_ctx.h"

/* Forward declarations for domain/app types */
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;
typedef struct s_app		t_app;
typedef struct s_render_ctx	t_render_ctx;

/* ========== Scene & App Cleanup ========== */

void						scene_free(t_scene *scene);
void						app_cleanup(t_app *app);
void						mlx_destroy_mem(t_render_ctx *ren);

#endif
