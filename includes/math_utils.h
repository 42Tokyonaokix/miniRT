/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/13 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

/* ========== Constants ========== */

# define EPS 1e-6
# define ERRORNO -1
/* ========== Numeric Helpers ========== */


/* ========== Quadratic Equation Solver ========== */

int		solve_quadratic(double a, double b, double c, double *t0, double *t1);
double	quad_min_solutoin(double a, double b, double c);

#endif
