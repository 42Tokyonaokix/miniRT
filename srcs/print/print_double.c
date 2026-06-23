/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	double_print(double n, char *s)
{
	printf("===\033[34mdouble_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s: %f\n", s, n);
	ft_putendl_fd("", 1);
}
