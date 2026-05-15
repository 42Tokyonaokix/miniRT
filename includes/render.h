/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 12:11:53 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "scene.h"
# include "intersect.h"

# define WIN_H 600
# define WIN_W 800

/* ========== Camera utils Functions ========== */
double		camera_half_w(t_camera camera);
double		camera_half_h(t_camera camera);

/* ========== Camera Functions ========== */
t_ray		generate_primary_ray(const t_camera *camera, int x, int y);
t_camera	build_camera_basis(t_camera camera);

/* ========== Shading Functions ========== */
t_color		shade(const t_scene *scene, const t_hit *hit, t_ray ray);

/* ========== Normal Functions ========== */

t_vec3		normal_sphere(const t_sphere *sphere, t_vec3 point);
t_vec3		normal_plane(const t_plane *plane);
t_vec3		normal_cylinder(const t_cylinder *cylinder, t_vec3 point);
t_vec3		face_forward(t_vec3 normal, t_ray ray);

#endif
