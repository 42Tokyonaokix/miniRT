/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/17 12:00:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	dispatch_line(t_scene *scene, char **tok, unsigned char *flags)
{
	int	flag;

	flag = dispatch_env(scene, tok, flags);
	if (flag != UNKNOWN)
		return (flag);
	flag = dispatch_object(scene, tok);
	if (flag != UNKNOWN)
		return (flag);
	if (flag == UNKNOWN)
		logging_status(tok[0], "UNknown identifier");
	return (FAILURE);
}

static int	parse_line(char *line, t_scene *scene, unsigned char *flags)
{
	char	**tokens;
	char	*head;
	int		ret;
	size_t	len;

	head = skip_space_tabs(line);
	if (*head == '\0' || *head == '\n')
		return (SUCCESS);
	len = ft_strlen(head);
	if (len > 0 && head[len - 1] == '\n')
		head[len - 1] = '\0';
	tokens = ft_split(head, ' ');
	if (!tokens || !tokens[0])	
		return (logging_status("parse_line: ft_split", "FATAL ERROR detected"),
			free_tokens(tokens), FAILURE);
	ret = dispatch_line(scene, tokens, flags);
	free_tokens(tokens);
	return (ret);
}

static int	check_required(unsigned char flags)
{
	if (!(flags & FLAG_A))
		return (logging_status("ambient", "Missing required"), FAILURE);
	if (!(flags & FLAG_C))
		return (logging_status("camera", "Missing required"), FAILURE);
	if (!(flags & FLAG_L))
		return (logging_status("light", "Missing required"), FAILURE);
	return (SUCCESS);
}

int	parse_scene(int fd, t_scene *scene)
{
	char			*line;
	unsigned char	flags;

	flags = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_line(line, scene, &flags) == FAILURE)
		{
			free(line);
			get_next_line(GNL_CLOSE);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (check_required(flags));
}
