/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include <stdio.h>

void	hit_print(t_hit hit, char *s)
{
	char	*type;

	type = "UNKNOWN";
	if (hit.obj_type == OBJ_CYLINDER)
		type = "OBJ_CYLINDER";
	else if (hit.obj_type == OBJ_PLANE)
		type = "OBJ_PLANE";
	else if (hit.obj_type == OBJ_SPHERE)
		type = "OBJ_SPHERE";
	printf("===\033[33mhit_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("point.x: %f\n", hit.point.x);
	printf("point.y: %f\n", hit.point.y);
	printf("point.z: %f\n", hit.point.z);
	printf("normal.x: %f\n", hit.normal.x);
	printf("normal.y: %f\n", hit.normal.y);
	printf("normal.z: %f\n", hit.normal.z);
	printf("obj_type: %s\n", type);
	ft_putendl_fd("", 1);
}
