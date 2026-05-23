/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 by natakaha                  #+#    #+#             */
/*   Updated: 2026/05/23 by natakaha                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "interact.h"
# include <stdio.h>

/* ========== ANSI Terminal Colors ========== */
# define COL_RESET   "\033[0m"
# define COL_DIM     "\033[2m"
# define COL_BOLD    "\033[1m"
# define COL_RED     "\033[31m"
# define COL_GREEN   "\033[32m"
# define COL_YELLOW  "\033[33m"
# define COL_BLUE    "\033[34m"
# define COL_MAG     "\033[35m"
# define COL_CYAN    "\033[36m"

/* ========== Print Mode ========== */
typedef enum e_print_mode
{
	PRINT_PREVIEW,
	PRINT_APPLY
}	t_print_mode;

/* ========== Logging ========== */
void	logging_err(char *arg1, char *message);
void	logging_sel(char *arg1, char *message);

/* ========== Box Panel ========== */
void	print_motion_box(t_input_state input, t_print_mode mode);

#endif
