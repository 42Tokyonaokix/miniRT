/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 02:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* sp/pl/cy のフィールド代入のみ (malloc・append は持たない) */

int	fill_sphere(char **tok, t_sphere *node)
{
	if (!parse_vec3(tok[1], &node->center))
		return (0);
	if (!parse_positive_double(tok[2], &node->radius))
		return (0);
	node->radius /= 2;
	return (parse_color(tok[3], &node->color));
}

int	fill_plane(char **tok, t_plane *node)
{
	if (!parse_vec3(tok[1], &node->point))
		return (0);
	if (!parse_direction(tok[2], &node->normal))
		return (0);
	return (parse_color(tok[3], &node->color));
}

int	fill_cylinder(char **tok, t_cylinder *node)
{
	if (!parse_vec3(tok[1], &node->center))
		return (0);
	if (!parse_direction(tok[2], &node->axis))
		return (0);
	if (!parse_positive_double(tok[3], &node->radius))
		return (0);
	node->radius /= 2;
	if (!parse_positive_double(tok[4], &node->height))
		return (0);
	return (parse_color(tok[5], &node->color));
}
