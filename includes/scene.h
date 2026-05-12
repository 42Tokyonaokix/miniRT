/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/12 21:35:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "math.h"

typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
}   t_obj_type;

typedef struct s_sphere
{
    t_vec3          center;
    double          radius;
    t_color         color;
    struct s_sphere *next;
}   t_sphere;

typedef struct s_plane
{
    t_vec3          point;
    t_vec3          normal;
    t_color         color;
    struct s_plane  *next;
}   t_plane;

typedef struct s_cylinder
{
    t_vec3              center;
    t_vec3              axis;
    double              radius;
    double              height;
    t_color             color;
    struct s_cylinder  *next;
}   t_cylinder;

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
    double  yaw;
    double  pitch;
}   t_camera;

typedef struct s_light
{
    t_vec3  position;
    double  ratio;
    t_color color;
}   t_light;

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
