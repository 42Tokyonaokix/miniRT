/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:05:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 23:09:02 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "scene.h"
# include "intersect.h"
# include "render.h"
# include "mlx_ctx.h"

typedef enum e_select_kind
{
    SEL_NONE,
    SEL_CAMERA,
    SEL_LIGHT,
    SEL_OBJECT
}   t_select_kind;

typedef struct s_selection
{
    t_select_kind   kind;
    t_obj_type      obj_type;
    void        *obj_ptr;
}   t_selection;

typedef struct s_input_track
{
    int         drag_active;
    int         drag_last_x;
    int         drag_last_y;
    int         drag_moved;
    long long   last_event_ms;
}   t_input_track;

typedef struct s_input_state
{
    t_selection     selected;
    t_input_track   track;
    int             dirty;
}   t_input_state;

typedef struct s_render_ctx
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_render_ctx;

typedef struct s_app
{
    t_scene         scene;
    t_render_ctx    render;
    t_input_state   input;
}   t_app;



int	app_init(t_app *app);

#endif
