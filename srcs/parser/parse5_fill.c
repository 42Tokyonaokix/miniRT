/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 23:29:09 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* sp/pl/cy のフィールド代入のみ (malloc・append は持たない) */

int	fill_sphere(char **tok, t_sphere *node)
{
	if (parse_vec3(tok[1], &node->center) != SUCCESS)
		return (FAILURE);
	if (parse_positive_double(tok[2], &node->radius) != SUCCESS)
		return (FAILURE);
	node->radius /= 2;
	return (parse_color(tok[3], &node->color, "sphere"));
}

int	fill_plane(char **tok, t_plane *node)
{
	if (parse_vec3(tok[1], &node->point) != SUCCESS)
		return (FAILURE);
	if (parse_direction(tok[2], &node->normal) != SUCCESS)
		return (FAILURE);
	return (parse_color(tok[3], &node->color, "plane"));
}

int	fill_cylinder(char **tok, t_cylinder *node)
{
	if (parse_vec3(tok[1], &node->center) != SUCCESS)
		return (FAILURE);
	if (parse_direction(tok[2], &node->axis) != SUCCESS)
		return (FAILURE);
	if (parse_positive_double(tok[3], &node->radius) != SUCCESS)
		return (FAILURE);
	node->radius /= 2;
	if (parse_positive_double(tok[4], &node->height) != SUCCESS)
		return (FAILURE);
	return (parse_color(tok[5], &node->color, "cylinder"));
}
