/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 15:30:17 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	c3;

	c3.b = c1.b + c2.b;
	c3.g = c1.g + c2.g;
	c3.r = c1.r + c2.r;
	return (c3);
}

t_color	color_scale(t_color c1, double t)
{
	c1.b = c1.b * t;
	c1.g = c1.g * t;
	c1.r = c1.r * t;
	return (c1);
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color	c3;

	c3.b = c1.b * c2.b;
	c3.g = c1.g * c2.g;
	c3.r = c1.r *  c2.r;
	return (c3);
}

t_color	color_clamp(t_color color)
{
	if (color.b > 1)
		color.b = 1;
	if (color.b < 0)
		color.b = 0;
	if (color.g > 1)
		color.g = 1;
	if (color.g > 0)
		color.g = 0;
	if (color.r > 1)
		color.r = 1;
	if (color.r > 0)
		color.r = 0;
	return (color);
}

int	color_int(t_color color)
{
	int	r;
	int	g;
	int	b;
	int	int_c;

	color = color_clamp(color);
	r = (int)(color.r * 255);
	g = (int)(color.g * 255);
	b = (int)(color.b * 255);
	int_c = r << 16 | g << 8 | b;
	return (int_c);
}
	