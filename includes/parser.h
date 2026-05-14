/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 16:10:12 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "scene.h"
# include "app.h"

/* ========== Parser Functions ========== */

int		parse_scene(const char *filename, t_scene *scene, t_app *app);
int		parse_ambient(char *line, t_ambient *ambient);
int		parse_camera(char *line, t_camera *camera);
int		parse_light(char *line, t_light *light);
int		parse_sphere(char *line, t_sphere **spheres, t_app *app);
int		parse_plane(char *line, t_plane **planes, t_app *app);
int		parse_cylinder(char *line, t_cylinder **cylinders, t_app *app);

/* ========== Parser Utilities ========== */

char	**parse_split(char *line);
double	parse_atof(char *str, int *error);
int		parse_vec3(char *str, t_vec3 *vec);
int		parse_color(char *str, t_color *color);
int		is_valid_float(char *str);

#endif

