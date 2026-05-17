/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 23:50:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 23:20:42 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* A/C/L の振り分けと重複検出 (フラグ管理) */

static int	handle_ambient(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_A)
		return (logging_status("ambient", "multiple detection"), FAILURE);
	if (parse_ambient(tok, &s->ambient) != SUCCESS)
		return (FAILURE);
	*flags |= FLAG_A;
	return (SUCCESS);
}

static int	handle_camera(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_C)
		return (logging_status("camera", "multiple detection"), FAILURE);
	if (parse_camera(tok, &s->camera) != SUCCESS)
		return (FAILURE);
	*flags |= FLAG_C;
	return (SUCCESS);
}

static int	handle_light(t_scene *s, char **tok, unsigned char *flags)
{
	if (*flags & FLAG_L)
		return (logging_status("light", "Duplicate light"), FAILURE);
	if (parse_light(tok, &s->light) != SUCCESS)
		return (FAILURE);
	*flags |= FLAG_L;
	return (SUCCESS);
}

int	dispatch_env(t_scene *scene, char **tok, unsigned char *flags)
{
	if (!ft_strcmp(tok[0], "A"))
		return (handle_ambient(scene, tok, flags));
	if (!ft_strcmp(tok[0], "C"))
		return (handle_camera(scene, tok, flags));
	if (!ft_strcmp(tok[0], "L"))
		return (handle_light(scene, tok, flags));
	return (UNKNOWN);
}
