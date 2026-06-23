/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	vec3_print(t_vec3 v1, char *s)
{
	printf("===\033[32mvec3_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s.x: %f\n", s, v1.x);
	printf("%s.y: %f\n", s, v1.y);
	printf("%s.z: %f\n", s, v1.z);
	ft_putendl_fd("", 1);
}
