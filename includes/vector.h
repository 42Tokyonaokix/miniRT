/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/13 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/* ========== Vec3 Type ========== */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* ========== Vec3 Operations ========== */

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double scalar);
t_vec3	vec3_div(t_vec3 v, double scalar);
t_vec3	vec3_neg(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
double	vec3_length(t_vec3 v);
double	vec3_length_sq(t_vec3 v);

/* ========== Vec3 Dot & Cross ========== */

double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* ========== Vec3 Interpolation ========== */

t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t);

/* ========== Vec3 Rotation (Rodrigues) ========== */

t_vec3	rodrigues_rotate(t_vec3 v, t_vec3 axis, double angle);

#endif
