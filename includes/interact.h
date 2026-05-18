/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 17:47:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACT_H
# define INTERACT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "memory.h"

/* Forward declarations */
typedef struct s_input_state	t_input_state;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_light			t_light;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_app			t_app;
typedef struct s_selection		t_selection;

typedef enum e_mac_code
{
	ESC = 53,
	W = 13,
	S = 1,
	A = 0,
	D = 2,
	Q = 12,
	E = 14,
	TAB = 48,
	SPACE = 49,
	ENTER = 36,
	LEFT_ARR = 123,
	UP_ARR = 126,
	RIGHT_ARR = 124,
	DOWN_ARR = 125,
}	t_mac_code;

typedef	enum e_mode
{
	TRANSLATE,
	ROTATE,
}	t_mode;

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
    void            *obj_ptr;
}   t_selection;

typedef enum e_intent
{
	T_FORWARD = 0,
	T_BACK,
	T_LEFT,
	T_RIGHT,
	T_DOWN,
	T_UP,
	R_LEFT,
	R_RIGHT,
	R_UP,
	R_DOWN,
}	t_intent;

typedef struct s_input_state
{
	t_selection     selected;
	int				start[10];
	int			    buf[10];
	t_mode			mode;
}   t_input_state;

/* ========== Intent Functions ========== */
void	interact_tab(t_app *app);
void	interact_space(t_app *app);
void	interact_enter(t_app *app);
void	interact_mouse_press(t_app *app, int x, int y);
void	interact_mouse_release(t_app *app, int x, int y);

/* ========== Selection Functions ========== */

/* ========== Transform Apply Functions ========== */

/* ========== Key Bindings ========== */
int	mlx_key_press(int keycode, void *param);
int	mlx_key_release(int keycode, void *param);

/* ========== Mouse Bindings ========== */
int	mlx_mouse_press(void *param);
int	mlx_mouse_release(void *param);

/* ========== HUD (optional) ========== */
void	time_press(int *ll_time);
void	time_release(int *start, int *buf);
int		time_get(void);

#endif
