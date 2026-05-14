/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 03:14:29 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACT_H
# define INTERACT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

/* Forward declarations */
typedef struct s_input_state	t_input_state;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_light			t_light;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_app			t_app;
typedef struct s_selection		t_selection;

# include "app.h"

/* ========== Intent Functions ========== */

/* ========== Selection Functions ========== */

/* ========== Transform Apply Functions ========== */

/* ========== Key Bindings ========== */

/* ========== Mouse Bindings ========== */

/* ========== HUD (optional) ========== */

#endif
