/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 00:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 12:00:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 値の検証と変換: atof/vec3/color と数値形式の妥当性 */

int	is_valid_float(char *str)
{
	int	i;
	int	dot;

	if (!str || !*str)
		return (FAILURE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (FAILURE);
	dot = 0;
	while (str[i])
	{
		if (str[i] == '.' && !dot)
			dot = 1;
		else if (!ft_isdigit(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

double	parse_atof(char *str, int *error)
{
	if (is_valid_float(str) != SUCCESS)
	{
		*error = FAILURE;
		return (0.0);
	}
	*error = SUCCESS;
	return (ft_atof(str));
}

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**parts;
	int		err;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (logging_status("parse_vec3: ft_split", "FATAL ERROR detected"),
			free_tokens(parts), FAILURE);
	vec->x = parse_atof(parts[0], &err);
	if (err != SUCCESS)
		return (logging_status(parts[0], "invalid float"),
			free_tokens(parts), FAILURE);
	vec->y = parse_atof(parts[1], &err);
	if (err != SUCCESS)
		return (logging_status(parts[1], "invalid float"),
			free_tokens(parts), FAILURE);
	vec->z = parse_atof(parts[2], &err);
	if (err != SUCCESS)
		return (logging_status(parts[2], "invalid float"),
			free_tokens(parts), FAILURE);
	free_tokens(parts);
	return (SUCCESS);
}

int	parse_color(char *str, t_color *color, char *obj_type)
{
	char	**parts;
	double	rgb[3];
	int		err;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (logging_status("parse_color: malloc", "FATAL ERROR detected"),
			free_tokens(parts), FAILURE);
	rgb[0] = parse_atof(parts[0], &err);
	if (!err)
		rgb[1] = parse_atof(parts[1], &err);
	if (!err)
		rgb[2] = parse_atof(parts[2], &err);
	free_tokens(parts);
	if (err)
		return (logging_status(obj_type, "Invalid color value"), FAILURE);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (logging_status(obj_type, "Color out of range\n"), FAILURE);
	color->r = rgb[0] / 255.0;
	color->g = rgb[1] / 255.0;
	color->b = rgb[2] / 255.0;
	return (SUCCESS);
}
