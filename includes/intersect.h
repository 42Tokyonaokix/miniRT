/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 20:41:14 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "vector.h"
# include "math_utils.h"
# include "color.h"

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

typedef enum e_point_type
{
	SIDE,
	TOP
}	t_point_type;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}   t_obj_type;

typedef struct s_ray
{
	t_vec3  origin;
	t_vec3  dir;
}   t_ray;

typedef struct s_hit
{
	t_vec3       point;
	t_vec3       normal;
	t_color      color;
	t_obj_type   obj_type;
	void        *obj_ptr;
}   t_hit;

/* ========== Intersection Functions ========== */
double	ray_plane_t(t_ray ray, t_plane plane);
double	ray_cylinder_t(t_ray ray, t_cylinder cyl);
t_hit	ray_plane_hit(t_ray ray, t_plane *plane);


/* ========== Find Closest Hit ========== */
t_vec3	ray_to_vec3(t_ray ray, double t);
void	hit_print(t_hit hit, char *s);
/* ========== Print Hit ========== */

#endif
