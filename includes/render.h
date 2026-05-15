/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 23:12:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "scene.h"
# include "intersect.h"
# include "color.h"

# define WIN_H 600
# define WIN_W 800
# define OK 0
# define NG 1

typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     light;
    t_sphere    *spheres;
    t_plane     *planes;
    t_cylinder  *cylinders;
}           t_scene;

/* ========== Camera utils Functions ========== */
double		camera_half_w(t_camera camera);
double		camera_half_h(t_camera camera);

/* ========== Camera Functions ========== */
int	        camera_build_basis(t_camera	*camera);

/* ========== Shading Functions ========== */
t_ray		generate_primary_ray(const t_camera *camera, int x, int y);
t_ray   	camera_pixel_ray(t_camera camera, int x, int y);
int	render_detect_color(t_hit hit, t_scene scene);

#endif
