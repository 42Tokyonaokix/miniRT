/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 00:36:09 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include "memory.h"
#include "mlx_ctx.h"
#include "app.h"
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
		return ((void)ft_dprintf(STDERR_FILENO, "%s", "Args Error\n"), EXIT_FAILURE);
	if (!is_valid_file_suffix((const char *)argv[1]))
		return ((void)ft_dprintf(STDERR_FILENO, "%s", "file prefix Error\n"), EXIT_FAILURE);
	ft_bzero(&app, sizeof(t_app));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return ((void)ft_dprintf(STDERR_FILENO, "%s", "Cannot open file\n"), EXIT_FAILURE);
	ok = parse_scene(fd, &app.scene);
	close(fd);
	/* debug */
	ok = app_init(&app);
	if (ok == OK)
	{
		render_loop(&app);
		mlx_put_image_to_window(app.render.mlx, app.render.win, app.render.img, 0, 0);
		mlx_loop(app.render.mlx);
	}	
	scene_free(&app.scene);
	if (ok != OK)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
