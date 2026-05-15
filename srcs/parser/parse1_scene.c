/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 21:21:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* シーン全体の制御 (gnl ループと dispatch、必須要素チェック) */

static int	dispatch_line(t_scene *scene, char **tok, unsigned char *flags)
{
	int	r;

	r = dispatch_env(scene, tok, flags);
	if (r != -1)
		return (r);
	r = dispatch_object(scene, tok);
	if (r != -1)
		return (r);
	ft_dprintf(2, "Unknown identifier: %s\n", tok[0]);
	return (0);
}

static int	parse_line(char *line, t_scene *scene, unsigned char *flags)
{
	char	**tokens;
	char	*head;
	int		ret;
	size_t	len;

	head = skip_space_tabs(line);
	if (*head == '\0' || *head == '\n')
		return (1);
	len = ft_strlen(head);
	if (len > 0 && head[len - 1] == '\n')
		head[len - 1] = '\0';
	tokens = ft_split(head, ' ');
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (0);
	}
	ret = dispatch_line(scene, tokens, flags);
	free_tokens(tokens);
	return (ret);
}

static int	check_required(unsigned char flags)
{
	if (!(flags & FLAG_A))
		return (ft_dprintf(2, "Missing required: ambient\n"), 0);
	if (!(flags & FLAG_C))
		return (ft_dprintf(2, "Missing required: camera\n"), 0);
	if (!(flags & FLAG_L))
		return (ft_dprintf(2, "Missing required: light\n"), 0);
	return (1);
}

int	parse_scene(int fd, t_scene *scene)
{
	char			*line;
	unsigned char	flags;

	flags = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!parse_line(line, scene, &flags))
		{
			free(line);
			get_next_line(GNL_CLOSE);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (check_required(flags));
}
