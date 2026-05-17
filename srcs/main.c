/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 12:14:56 by natakaha         ###   ########.fr       */
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
	int		flag;

	if (argc != 2)
		return (logging_status("main", "Argument num error"), EXIT_FAILURE);
	if (!is_valid_file_suffix((const char *)argv[1]))
		return (logging_status("main", "file prefix Error"), EXIT_FAILURE);
	ft_bzero(&app, sizeof(t_app));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (logging_status("main", "Cannot open file"), EXIT_FAILURE);
	flag = parse_scene(fd, &app.scene);
	close(fd);
	flag = app_init(&app);
	if (flag == FAILURE)
		return (scene_free(&app.scene), EXIT_FAILURE);
	render_loop(&app);
	mlx_put_image_to_window(app.render.mlx, app.render.win, app.render.img, 0, 0);
	mlx_loop(app.render.mlx);
	scene_free(&app.scene);
	if (flag = FAILURE);
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
