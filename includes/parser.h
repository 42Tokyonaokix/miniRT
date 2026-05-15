/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 16:37:58 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "app.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "scene.h"
# include "vector.h"
# include "render.h"

typedef enum e_token_flags
{
	FLAG_A = 1 << 0,
	FLAG_C = 1 << 1,
	FLAG_L = 1 << 2
}	t_token_flags;

int		parse_scene(int fd, t_scene *scene);

int		parse_ambient(char **tok, t_ambient *ambient);
int		parse_camera(char **tok, t_camera *camera);
int		parse_light(char **tok, t_light *light);
int		parse_sphere(char **tok, t_sphere **spheres);
int		parse_plane(char **tok, t_plane **planes);
int		parse_cylinder(char **tok, t_cylinder **cylinders);

int		dispatch_env(t_scene *scene, char **tok, unsigned char *flags);
int		dispatch_object(t_scene *scene, char **tok);

int		fill_sphere(char **tok, t_sphere *node);
int		fill_plane(char **tok, t_plane *node);
int		fill_cylinder(char **tok, t_cylinder *node);

double	parse_atof(char *str, int *error);
int		parse_vec3(char *str, t_vec3 *vec);
int		parse_color(char *str, t_color *color);
int		is_valid_float(char *str);

int		parse_ranged_double(char *str, double min, double max, double *out);
int		parse_positive_double(char *str, double *out);
int		parse_direction(char *str, t_vec3 *vec);

char	*skip_space_tabs(char *str);
void	free_tokens(char **tokens);
int		count_tokens(char **tokens);

#endif
