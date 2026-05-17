/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 12:01:12 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* sp/pl/cy の振り分けとノード確保・代入・リスト追加 */

int	parse_sphere(char **tok, t_sphere **spheres)
{
	t_sphere	*node;

	if (count_tokens(tok) != 4)
		return (logging_status("sphere", "Invalid sphere format"), FAILURE);
	node = malloc(sizeof(t_sphere));
	if (!node)
		return (logging_status("parse_sphere", "FATAL ERROR detected"), FAILURE);
	if (fill_sphere(tok, node) != SUCCESS)
		return (free(node), FAILURE);
	node->next = *spheres;
	*spheres = node;
	return (SUCCESS);
}

int	parse_plane(char **tok, t_plane **planes)
{
	t_plane	*node;

	if (count_tokens(tok) != 4)
		return (logging_status("plane", "Invalid plane format\n"), FAILURE);
	node = malloc(sizeof(t_plane));
	if (!node)
		return (logging_status("parse_plane", "FATAL ERROR detected"), FAILURE);
	if (fill_plane(tok, node) != SUCCESS)
		return (free(node), FAILURE);
	node->next = *planes;
	*planes = node;
	return (SUCCESS);
}

int	parse_cylinder(char **tok, t_cylinder **cylinders)
{
	t_cylinder	*node;

	if (count_tokens(tok) != 6)
		return (logging_status("cylinder", "Invalid cylinder format"), FAILURE);
	node = malloc(sizeof(t_cylinder));
	if (!node)
		return (logging_status("cylinder", "Memory allocation failed"), FAILURE);
	if (fill_cylinder(tok, node) != SUCCESS)
		return (free(node), FAILURE);
	node->next = *cylinders;
	*cylinders = node;
	return (SUCCESS);
}

int	dispatch_object(t_scene *scene, char **tok)
{
	if (!ft_strcmp(tok[0], "sp"))
		return (parse_sphere(tok, &scene->spheres));
	if (!ft_strcmp(tok[0], "pl"))
		return (parse_plane(tok, &scene->planes));
	if (!ft_strcmp(tok[0], "cy"))
		return (parse_cylinder(tok, &scene->cylinders));
	return (UNKNOWN);
}
