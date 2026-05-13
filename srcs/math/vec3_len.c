/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:15 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 14:19:41 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

double	vec3_sq(t_vec3 *v1)
{
	return ((v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z));
}

double	vec3_abs(t_vec3 *v1)
{
	return (sqrt(vec3_sq(v1)));
}

t_vec3	vec3_normalize(t_vec3 *v1)
{
	t_vec3	v2;
	double	n;
	
	n = vec3_abs(v1);
	v2 = vec3_scale(v1, 1 / n);
	return (v2);
}

void	double_print(double n, char *s)
{
	printf("===\033[31m%s\033[0m: \033[34mdouble_print\033[0m===\n", s);
	printf("%s: %f\n", s, n);
	ft_putendl_fd("", 1);
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
	vec3_print(&v1, "v1");
	v2.x = ft_atoi(argv[4]);
	v2.y = ft_atoi(argv[5]);
	v2.z = ft_atoi(argv[6]);
	vec3_print(&v2, "v2");
	n = ft_atoi(argv[7]);
	v3 = vec3_add(&v1, &v2);
	// vec3_print(&v3);
	v3 = vec3_sub(&v1, &v2);
	// vec3_print(&v3);
	v3 = vec3_scale(&v1, n);
	// vec3_print(&v3);
	n = vec3_sq(&v1);
	double_print(n, "v1_sqlen");
	n = vec3_abs(&v1);
	double_print(n, "v1_len");
	v3 = vec3_normalize(&v1);
	vec3_print(&v3, "v1_normalized");
	n = vec3_abs(&v3);
	double_print(n, "normal_len");
	(void)v3;
	return (EXIT_SUCCESS);
}
 */
