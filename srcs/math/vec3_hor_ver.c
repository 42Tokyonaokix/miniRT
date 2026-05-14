/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_hor_ver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 09:09:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

t_vec3	vec3_hor(t_vec3 v, t_vec3 axis)
{
	t_vec3	v_hor;
	double	den;
	double	scale;
	
	den = vec3_sq(axis);
	if (den < EPS * EPS)
		return ((t_vec3){0.0, 0.0, 0.0});
	scale = vec3_dot(v, axis) / den;
	v_hor = vec3_scale(axis, scale);
	return (v_hor);
}

t_vec3	vec3_ver(t_vec3 v, t_vec3 axis)
{
	t_vec3	v_hor;
	t_vec3	v_ver;

	v_hor = vec3_hor(v, axis);
	v_ver = vec3_sub(v, v_hor);
	return (v_ver);
}

/* 
int	main(int argc, char **argv)
{
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	v3;
	t_vec3	v4;
	t_vec3	v5;
	
	if (argc != 7)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	v1.x = ft_atoi(argv[1]);
	v1.y = ft_atoi(argv[2]);
	v1.z = ft_atoi(argv[3]);
	vec3_print(v1, "v1");
	v2.x = ft_atoi(argv[4]);
	v2.y = ft_atoi(argv[5]);
	v2.z = ft_atoi(argv[6]);
	vec3_print(v2, "v2");
	v3 = vec3_hor(v1, v2);
	vec3_print(v3, "horizontal");
	v4 = vec3_ver(v1, v2);
	vec3_print(v3, "horizontal");
	v5 = vec3_add(v3, v4);
	vec3_print(v5, "(hor + ver)");
	vec3_print(v1, "v1");
	return (EXIT_SUCCESS);
}
 */
