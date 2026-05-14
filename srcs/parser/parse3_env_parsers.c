/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_env_parsers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 02:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* A/C/L のフィールド代入のみ (重複検出・フラグ管理は持たない) */

int	parse_ambient(char **tok, t_ambient *ambient)
{
	if (count_tokens(tok) != 3)
		return (ft_dprintf(2, "Invalid ambient format\n"), 0);
	if (!parse_ranged_double(tok[1], 0.0, 1.0, &ambient->ratio))
		return (0);
	if (!parse_color(tok[2], &ambient->color))
		return (0);
	return (1);
}

int	parse_camera(char **tok, t_camera *camera)
{
	if (count_tokens(tok) != 4)
		return (ft_dprintf(2, "Invalid camera format\n"), 0);
	if (!parse_vec3(tok[1], &camera->position))
		return (0);
	if (!parse_direction(tok[2], &camera->forward))
		return (0);
	if (!parse_ranged_double(tok[3], 0.0, 180.0, &camera->fov_deg))
		return (0);
	return (1);
}

int	parse_light(char **tok, t_light *light)
{
	if (count_tokens(tok) != 4)
		return (ft_dprintf(2, "Invalid light format\n"), 0);
	if (!parse_vec3(tok[1], &light->position))
		return (0);
	if (!parse_ranged_double(tok[2], 0.0, 1.0, &light->ratio))
		return (0);
	if (!parse_color(tok[3], &light->color))
		return (0);
	return (1);
}
