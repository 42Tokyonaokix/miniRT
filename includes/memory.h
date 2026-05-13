/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 11:48:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/* Forward declarations for domain/app types */
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;
typedef struct s_app		t_app;

/* ========== Intrusive List Management ========== */

void	sphere_append(t_sphere **head, t_sphere *new_node);
void	sphere_clear(t_sphere **head);
void	plane_append(t_plane **head, t_plane *new_node);
void	plane_clear(t_plane **head);
void	cylinder_append(t_cylinder **head, t_cylinder *new_node);
void	cylinder_clear(t_cylinder **head);

/* ========== Scene & App Cleanup ========== */

void	scene_free(t_scene *scene);
void	app_cleanup(t_app *app);

#endif
