/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 00:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 00:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 値の検証と変換: atof/vec3/color と数値形式の妥当性 */

int	is_valid_float(char *str)
{
	int	i;
	int	dot;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	dot = 0;
	while (str[i])
	{
		if (str[i] == '.' && !dot)
			dot = 1;
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

double	parse_atof(char *str, int *error)
{
	if (!is_valid_float(str))
	{
		*error = 1;
		return (0.0);
	}
	*error = 0;
	return (ft_atof(str));
}

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**parts;
	int		err;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), 0);
	vec->x = parse_atof(parts[0], &err);
	if (err)
		return (free_tokens(parts), 0);
	vec->y = parse_atof(parts[1], &err);
	if (err)
		return (free_tokens(parts), 0);
	vec->z = parse_atof(parts[2], &err);
	free_tokens(parts);
	return (!err);
}

int	parse_color(char *str, t_color *color)
{
	char	**parts;
	double	rgb[3];
	int		err;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), 0);
	rgb[0] = parse_atof(parts[0], &err);
	if (!err)
		rgb[1] = parse_atof(parts[1], &err);
	if (!err)
		rgb[2] = parse_atof(parts[2], &err);
	free_tokens(parts);
	if (err)
		return (ft_dprintf(2, "Invalid color value\n"), 0);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (ft_dprintf(2, "Color out of range\n"), 0);
	color->r = rgb[0] / 255.0;
	color->g = rgb[1] / 255.0;
	color->b = rgb[2] / 255.0;
	return (1);
}
