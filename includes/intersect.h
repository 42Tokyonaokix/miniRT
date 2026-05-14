/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 03:14:17 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "color.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "math_utils.h"
# include "vector.h"

typedef struct s_sphere
{
	struct s_sphere		*next;
	t_vec3				center;
	double				radius;
	t_color				color;
}						t_sphere;

typedef struct s_plane
{
	struct s_plane		*next;
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
}						t_plane;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
	t_vec3				center;
	t_vec3				axis;
	double				radius;
	double				height;
	t_color				color;
}						t_cylinder;

typedef enum e_point_type
{
	SIDE,
	CAPS,
}						t_point_type;

typedef enum e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}						t_obj_type;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				dir;
}						t_ray;

typedef struct s_hit
{
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	t_obj_type			obj_type;
	void				*obj_ptr;
}						t_hit;

/* ========== Ray–Sphere ========== */
double					ray_sphere_t(t_ray ray, t_sphere sphere);
t_hit					ray_sphere_hit(t_ray ray, t_sphere *sphere);

/* ========== Ray–Plane ========== */
double					ray_plane_t(t_ray ray, t_plane plane);
t_hit					ray_plane_hit(t_ray ray, t_plane *plane);

/* ========== Ray–Cylinder ========== */
double					ray_cylinder_t(t_ray ray, t_cylinder cyl,
							t_point_type *type);
t_hit					ray_cylinder_hit(t_ray ray, t_cylinder *cyl);
bool					if_valid_side_point(t_vec3 point, t_cylinder cyl);
bool					if_valid_caps_point(t_vec3 point, t_cylinder cyl);

/* ========== Ray Helpers ========== */
t_vec3					ray_to_vec3(t_ray ray, double t);

/* ========== Debug Print ========== */
void					hit_print(t_hit hit, char *s);

#endif
