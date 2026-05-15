/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 23:21:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ctx.h"

void	error_message(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO, "miniRT: %s: %s\n", arg1, message);
}
