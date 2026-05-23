/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/22 02:57:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACT_H
# define INTERACT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "memory.h"
# include "render.h"

/* Forward declarations */
typedef struct s_input_state	t_input_state;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_light			t_light;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_app			t_app;

typedef enum e_code
{
	ESC = 65307,
	W = 119,
	S = 115,
	A = 97,
	D = 100,
	Q = 113,
	E = 101,
	TAB = 65289,
	SPACE = 32,
	ENTER = 65293,
	LEFT_ARR = 65361,
	UP_ARR = 65362,
	RIGHT_ARR = 65363,
	DOWN_ARR = 65364,
}								t_code;

// typedef enum e_keycode
// {
// 	ESC = 53,
// 	W = 13,
// 	S = 1,
// 	A = 0,
// 	D = 2,
// 	Q = 12,
// 	E = 14,
// 	TAB = 48,
// 	SPACE = 49,
// 	ENTER = 36,
// 	LEFT_ARR = 123,
// 	UP_ARR = 126,
// 	RIGHT_ARR = 124,
// 	DOWN_ARR = 125,
// }								t_keycode;

typedef enum e_mousecode
{
	LEFT = 1,
	MIDDLE = 2,
	RIGHT = 3,
	H_UP = 4,
	H_DOWN = 5,
}								t_mousecode;

typedef enum e_select_kind
{
	SEL_NONE,
	SEL_CAMERA,
	SEL_LIGHT,
	SEL_OBJECT
}								t_select_kind;

typedef enum e_intent
{
	T_FORWARD = 0,
	T_UP = 1,
	T_RIGHT = 2,
	R_UP = 3,
	R_RIGHT = 4,
}								t_intent;

typedef struct s_selection
{
	t_select_kind				kind;
	t_obj_type					obj_type;
	void						*obj_ptr;
}								t_selection;

typedef struct s_move
{
	t_vec3						axis;
	double						angle;
	t_vec3						v_tls;
}								t_move;

typedef struct s_input_state
{
	t_selection					selected;
	t_move						move;
	int							buf[5];
	int							input[5];
}								t_input_state;

# include "translate.h"

/* ========== Intent Functions ========== */

/* ========== Selection Functions ========== */
void							interact_next_selection(t_scene *scene,
									t_selection *current);
t_select_kind					interact_print_selection(t_select_kind kind);
void							interact_print_obj(t_obj_type type);
void							*interact_select_ptr(t_scene *scene,
									t_select_kind kind);

/* ========== Key Bindings ========== */
int								mlx_key_press(int keycode, void *param);
int								mlx_key_release(int keycode, void *param);

/* ========== Mouse Bindings ========== */
int								mlx_mouse_press(int button, int x, int y,
									void *param);
int								mlx_mouse_release(int button, int x, int y,
									void *param);
void							mouse_left_press(t_app *app, int x, int y);
void							mouse_right_press(t_app *app, int x, int y);
void							mouse_left_release(t_app *app, int x, int y);
void							mouse_right_release(t_app *app, int x, int y);

/* ========== HUD (optional) ========== */
void							time_press(int *ll_time);
void							time_release(int *start, int *buf);
int								time_get(void);

#endif
