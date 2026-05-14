/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 23:50:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 01:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* A/C/L の振り分けと重複検出 (フラグ管理) */

static int	handle_ambient(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_A)
		return (ft_dprintf(2, "Duplicate ambient\n"), 0);
	if (!parse_ambient(tok, &s->ambient))
		return (0);
	*flags |= FLAG_A;
	return (1);
}

static int	handle_camera(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_C)
		return (ft_dprintf(2, "Duplicate camera\n"), 0);
	if (!parse_camera(tok, &s->camera))
		return (0);
	*flags |= FLAG_C;
	return (1);
}

static int	handle_light(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_L)
		return (ft_dprintf(2, "Duplicate light\n"), 0);
	if (!parse_light(tok, &s->light))
		return (0);
	*flags |= FLAG_L;
	return (1);
}

int	dispatch_env(t_scene *scene, char **tok, unsigned char *flags)
{
	if (!ft_strcmp(tok[0], "A"))
		return (handle_ambient(scene, tok, flags));
	if (!ft_strcmp(tok[0], "C"))
		return (handle_camera(scene, tok, flags));
	if (!ft_strcmp(tok[0], "L"))
		return (handle_light(scene, tok, flags));
	return (-1);
}
