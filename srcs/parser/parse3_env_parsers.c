/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_env_parsers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 11:59:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* A/C/L のフィールド代入のみ (重複検出・フラグ管理は持たない) */

int	parse_ambient(char **tok, t_ambient *ambient)
{
	if (count_tokens(tok) != 3)
		return (logging_status("ambient", "Invalid format"), FAILURE);
	if (parse_ranged_double(tok[1], 0.0, 1.0, &ambient->ratio) != SUCCESS)
		return (logging_status("ambient", "Value out of range"), FAILURE);
	if (parse_color(tok[2], &ambient->color, "ambient") != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_camera(char **tok, t_camera *camera)
{
	if (count_tokens(tok) != 4)
		return (logging_status("camera", "Invalid format"), FAILURE);
	if (parse_vec3(tok[1], &camera->position) != SUCCESS)
		return (FAILURE);
	if (parse_direction(tok[2], &camera->forward) != SUCCESS)
		return (FAILURE);
	if (parse_ranged_double(tok[3], 0.0, 180.0, &camera->fov_deg) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_light(char **tok, t_light *light)
{
	if (count_tokens(tok) != 4)
		return (logging_status(*tok, "Invalid light format\n"), FAILURE);
	if (parse_vec3(tok[1], &light->position) != SUCCESS)
		return (FAILURE);
	if (parse_ranged_double(tok[2], 0.0, 1.0, &light->ratio) != SUCCESS)
		return (FAILURE);
	if (parse_color(tok[3], &light->color, "light") != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
