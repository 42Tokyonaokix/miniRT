/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/12 21:35:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACT_H
# define INTERACT_H

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

# include "app.h"

/* ========== Intent Functions ========== */

void	intent_translate(t_input_state *input, t_scene *scene, t_vec3 delta);
void	intent_rotate(t_input_state *input, t_scene *scene, t_vec3 axis,
			double angle);
void	intent_select_next(t_input_state *input, t_scene *scene);
void	intent_select_object(t_input_state *input, t_scene *scene,
			int obj_type, void *obj_ptr);
void	intent_request_render(t_input_state *input);
void	intent_quit(t_input_state *input);

/* ========== Selection Functions ========== */

void	selection_next(t_selection *sel, const t_scene *scene);
void	selection_pick(t_selection *sel, const t_scene *scene, t_ray ray);

/* ========== Transform Apply Functions ========== */

void	apply_translate_camera(t_camera *camera, t_vec3 delta);
void	apply_translate_light(t_light *light, t_vec3 delta);
void	apply_translate_sphere(t_sphere *sphere, t_vec3 delta);
void	apply_translate_plane(t_plane *plane, t_vec3 delta);
void	apply_translate_cylinder(t_cylinder *cylinder, t_vec3 delta);

void	apply_rotate_camera(t_camera *camera, t_vec3 axis, double angle);
void	apply_rotate_light(t_light *light, t_vec3 axis, double angle);
void	apply_rotate_sphere(t_sphere *sphere, t_vec3 axis, double angle);
void	apply_rotate_plane(t_plane *plane, t_vec3 axis, double angle);
void	apply_rotate_cylinder(t_cylinder *cylinder, t_vec3 axis, double angle);

/* ========== Key Bindings ========== */

int		on_key_press(int keycode, t_app *app);
int		on_key_release(int keycode, t_app *app);

/* ========== Mouse Bindings ========== */

int		on_mouse_press(int button, int x, int y, t_app *app);
int		on_mouse_release(int button, int x, int y, t_app *app);
int		on_mouse_move(int x, int y, t_app *app);

/* ========== HUD (optional) ========== */

void	draw_hud(t_app *app);

#endif
