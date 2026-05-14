/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 16:12:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

/* 
int	main(int argc, char **argv)
{
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	v3;
	double	n;
	
	if (argc != 8)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	v1.x = ft_atoi(argv[1]);
	v1.y = ft_atoi(argv[2]);
	v1.z = ft_atoi(argv[3]);
	v2.x = ft_atoi(argv[4]);
	v2.y = ft_atoi(argv[5]);
	v2.z = ft_atoi(argv[6]);
	v1 = vec3_normalize(&v1);
	v2 = vec3_normalize(&v2);
	vec3_print(&v1, "v1");
	vec3_print(&v2, "v2");
	n = vec3_dot(&v1, &v2);
	double_print(n, "dot");
	v3 = vec3_cross(&v1, &v2);
	vec3_print(&v3, "cross");
	(void)v3;
	return (EXIT_SUCCESS);
}
 */