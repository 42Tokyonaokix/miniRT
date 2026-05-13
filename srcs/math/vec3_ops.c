/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:15 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 14:17:02 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

t_vec3	vec3_add(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v3;
	
	v3.x = v1->x + v2->x;
	v3.y = v1->y + v2->y;
	v3.z = v1->z + v2->z;
	return (v3);
}

t_vec3	vec3_sub(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v3;
	
	v3.x = v1->x - v2->x;
	v3.y = v1->y - v2->y;
	v3.z = v1->z - v2->z;
	return (v3);
}

t_vec3	vec3_scale(t_vec3 *v1, double n)
{
	t_vec3	v2;
	
	v2.x = v1->x * n;
	v2.y = v1->y * n;
	v2.z = v1->z * n;
	return (v2);
}

void	vec3_print(t_vec3 *v1, char *s)
{
	printf("===\033[31m%s\033[0m: \033[32mvec3_print\033[0m===\n", s);
	printf("%s->x: %f\n", s, v1->x);
	printf("%s->y: %f\n", s, v1->y);
	printf("%s->z: %f\n", s, v1->z);
	ft_putendl_fd("", 1);
}
