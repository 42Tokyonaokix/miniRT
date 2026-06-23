/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"

void	logging_status(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		COL_DIM "│" COL_RESET
		" " COL_DIM COL_BOLD "INF" COL_RESET
		"  %s  " COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}

void	logging_err(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		"Error\n"
		COL_RED COL_BOLD
		"%s  " COL_RESET COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}

void	logging_sel(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		COL_DIM "│" COL_RESET
		" " COL_CYAN COL_BOLD "SEL" COL_RESET
		"  %s  " COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}
