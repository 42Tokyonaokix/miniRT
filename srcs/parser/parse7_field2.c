/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse11_field2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 01:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 01:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 値の制約チェック: ranged/positive/direction */

int	parse_ranged_double(char *str, double min, double max, double *out)
{
	int	err;

	*out = parse_atof(str, &err);
	if (err || *out < min || *out > max)
		return (ft_dprintf(2, "Value out of range\n"), 0);
	return (1);
}

int	parse_positive_double(char *str, double *out)
{
	int	err;

	*out = parse_atof(str, &err);
	if (err || *out <= 0)
		return (ft_dprintf(2, "Value must be positive\n"), 0);
	return (1);
}

int	parse_direction(char *str, t_vec3 *vec)
{
	if (!parse_vec3(str, vec))
		return (0);
	if (vec->x < -1.0 || vec->x > 1.0
		|| vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0)
		return (ft_dprintf(2, "Direction component out of [-1,1]\n"), 0);
	if (vec3_abs(*vec) == 0)
		return (ft_dprintf(2, "Zero direction vector\n"), 0);
	*vec = vec3_normalize(*vec);
	return (1);
}
