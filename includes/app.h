/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:05:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/06/23 19:08:02 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "scene.h"
# include "intersect.h"
# include "interact.h"
# include "render.h"
# include "mlx_ctx.h"

typedef struct s_app
{
	t_scene			scene;
	t_render_ctx	render;
	t_input_state	input;
}	t_app;

int	app_init(t_app *app);

#endif
