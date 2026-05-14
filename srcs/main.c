/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/15 03:48:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include "memory.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

static bool	is_valid_file_suffix(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3)
		return (false);
	file_name += len - 3;
	if (ft_strcmp(file_name, ".rt"))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_app	app;
	int		fd;
	int		ok;

	if (argc != 2)
		return ((void)ft_dprintf(2, "%s", "Args Error\n"), 1);
	if (!is_valid_file_suffix((const char *)argv[1]))
		return ((void)ft_dprintf(2, "%s", "file prefix Error\n"), 1);
	ft_bzero(&app, sizeof(t_app));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return ((void)ft_dprintf(2, "%s", "Cannot open file\n"), 1);
	ok = parse_scene(fd, &app.scene);
	close(fd);
	scene_free(&app.scene);
	if (!ok)
		return (1);
	return (0);
}
