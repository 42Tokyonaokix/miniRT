/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 00:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/06/20 04:17:53 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* vec3 / color フィールドのパース（妥当性検証は utils2_valid.c） */

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**parts;
	int		err;

	if (!is_valid_comma(str))
		return (logging_err(str, "Invalid vector format"), FAILURE);
	parts = ft_split(str, ',');
	if (!parts)
		return (logging_err("parse_vec3", "Memory allocation failed"),
			free_tokens(parts), FAILURE);
	vec->x = parse_atof(parts[0], &err);
	if (err != SUCCESS)
		return (logging_err(parts[0], "Invalid float"), free_tokens(parts),
			FAILURE);
	vec->y = parse_atof(parts[1], &err);
	if (err != SUCCESS)
		return (logging_err(parts[1], "Invalid float"), free_tokens(parts),
			FAILURE);
	vec->z = parse_atof(parts[2], &err);
	if (err != SUCCESS)
		return (logging_err(parts[2], "Invalid float"), free_tokens(parts),
			FAILURE);
	free_tokens(parts);
	return (SUCCESS);
}

int	parse_color(char *str, t_color *color, char *obj_type)
{
	char	**parts;
	double	rgb[3];
	int		err;

	if (!is_valid_comma(str))
		return (logging_err(str, "Invalid color format"), FAILURE);
	if (ft_strchr(str, '.'))
		return (logging_err(str, "Color must be integer"), FAILURE);
	parts = ft_split(str, ',');
	if (!parts)
		return (logging_err("parse_color", "Memory allocation failed"),
			free_tokens(parts), FAILURE);
	rgb[0] = parse_atof(parts[0], &err);
	if (!err)
		rgb[1] = parse_atof(parts[1], &err);
	if (!err)
		rgb[2] = parse_atof(parts[2], &err);
	free_tokens(parts);
	if (err)
		return (logging_err(obj_type, "Invalid color value"), FAILURE);
	return (assign_color(color, rgb, obj_type));
}
