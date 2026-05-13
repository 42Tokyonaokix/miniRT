/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/13 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/* ========== Color Type ========== */

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

/* ========== Color Operations ========== */

t_color	color_add(t_color a, t_color b);
t_color	color_scale(t_color c, double scalar);
t_color	color_mul(t_color a, t_color b);
t_color	color_clamp(t_color c);
int		color_to_int(t_color c);
t_color	color_from_int(int rgb);

#endif
