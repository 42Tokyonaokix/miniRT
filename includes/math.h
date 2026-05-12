/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 07:12:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include_next <math.h>

/* ========== Basic Types ========== */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	int			obj_type;
	void		*obj_ptr;
}	t_hit;

/* ========== vec3 Operations ========== */

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double scalar);
t_vec3	vec3_normalize(t_vec3 v);
double	vec3_length(t_vec3 v);
double	vec3_length_sq(t_vec3 v);

/* ========== vec3 Dot & Cross ========== */

double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* ========== Color Operations ========== */

t_color	color_add(t_color a, t_color b);
t_color	color_scale(t_color c, double scalar);
t_color	color_mul(t_color a, t_color b);
int		color_to_int(t_color c);

/* ========== Rodrigues Rotation ========== */

t_vec3	rodrigues_rotate(t_vec3 v, t_vec3 axis, double angle);

#endif

