/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 02:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 02:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* sp/pl/cy の振り分けとノード確保・代入・リスト追加 */

int	parse_sphere(char **tok, t_sphere **spheres)
{
	t_sphere	*node;

	if (count_tokens(tok) != 4)
		return (ft_dprintf(2, "Invalid sphere format\n"), 0);
	node = malloc(sizeof(t_sphere));
	if (!node)
		return (ft_dprintf(2, "Memory allocation failed\n"), 0);
	if (!fill_sphere(tok, node))
		return (free(node), 0);
	node->next = *spheres;
	*spheres = node;
	return (1);
}

int	parse_plane(char **tok, t_plane **planes)
{
	t_plane	*node;

	if (count_tokens(tok) != 4)
		return (ft_dprintf(2, "Invalid plane format\n"), 0);
	node = malloc(sizeof(t_plane));
	if (!node)
		return (ft_dprintf(2, "Memory allocation failed\n"), 0);
	if (!fill_plane(tok, node))
		return (free(node), 0);
	node->next = *planes;
	*planes = node;
	return (1);
}

int	parse_cylinder(char **tok, t_cylinder **cylinders)
{
	t_cylinder	*node;

	if (count_tokens(tok) != 6)
		return (ft_dprintf(2, "Invalid cylinder format\n"), 0);
	node = malloc(sizeof(t_cylinder));
	if (!node)
		return (ft_dprintf(2, "Memory allocation failed\n"), 0);
	if (!fill_cylinder(tok, node))
		return (free(node), 0);
	node->next = *cylinders;
	*cylinders = node;
	return (1);
}

int	dispatch_object(t_scene *scene, char **tok)
{
	if (!ft_strcmp(tok[0], "sp"))
		return (parse_sphere(tok, &scene->spheres));
	if (!ft_strcmp(tok[0], "pl"))
		return (parse_plane(tok, &scene->planes));
	if (!ft_strcmp(tok[0], "cy"))
		return (parse_cylinder(tok, &scene->cylinders));
	return (-1);
}
