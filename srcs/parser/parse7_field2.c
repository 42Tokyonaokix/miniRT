/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7_field2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 01:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 23:15:14 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 値の制約チェック: ranged/positive/direction */

int	parse_ranged_double(char *str, double min, double max, double *out)
{
	int	err;

	*out = parse_atof(str, &err);
	if (err || *out < min || *out > max)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_positive_double(char *str, double *out)
{
	int	err;

	*out = parse_atof(str, &err);
	if (err || *out <= 0)
		return (logging_status(str, "Value must be positive"), FAILURE);
	return (SUCCESS);
}

int	parse_direction(char *str, t_vec3 *vec)
{
	if (parse_vec3(str, vec) != SUCCESS)
		return (FAILURE);
	if (vec->x < -1.0 || vec->x > 1.0
		|| vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0)
		return (logging_status(str, "Direction component out of [-1,1]"), FAILURE);
	if (vec3_abs(*vec) == 0)
		return (logging_status(str, "Zero direction vector\n"), FAILURE);
	*vec = vec3_normalize(*vec);
	return (SUCCESS);
}
