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
# include "math_utils.h"
# include <math.h>

/* ========== Vec3 Type ========== */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* ========== Vec3 Operations ========== */
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_scale(t_vec3 v1, double n);
double	vec3_sq(t_vec3 v1);
double	vec3_abs(t_vec3 v1);
t_vec3	vec3_normalize(t_vec3 v1);


/* ========== Vec3 print ========== */
void	vec3_print(t_vec3 v1, char *s);
void	double_print(double n, char *s);

/* ========== Vec3 Dot & Cross ========== */

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);

/* ========== Vec3 hor ver ========== */
t_vec3	vec3_ver(t_vec3 v, t_vec3 axis);
t_vec3	vec3_hor(t_vec3 v, t_vec3 axis);


/* ========== Vec3 Rotation (Rodrigues) ========== */



#endif
