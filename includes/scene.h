/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 21:57:12 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "vector.h"
# include "color.h"
# include "math.h"

typedef struct s_ambient
{
    double  ratio;
    t_color color;
}   t_ambient;

typedef struct s_camera
{
    t_vec3  position;
    t_vec3  forward;
    t_vec3  right;
    t_vec3  up;
    double  fov_deg;
}   t_camera;

typedef struct s_light
{
    t_vec3  position;
    double  ratio;
    t_color color;
}   t_light;

typedef struct s_sphere     t_sphere;
typedef struct s_plane      t_plane;
typedef struct s_cylinder   t_cylinder;

typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     light;
    t_sphere    *spheres;
    t_plane     *planes;
    t_cylinder  *cylinders;
}   t_scene;

#endif
