/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/18 17:47:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
# include <sys/time.h>

void	time_press(int *ll_time)
{
	*ll_time = time_get();
}

void	time_release(int *start, int *buf_time)
{
	int	end;

	end = time_get();
	*buf_time += end - *start;
	*start = 0;
}

int	time_get(void)
{
	struct timeval	time;
	long long		ll_time;	
	int				int_time;

	gettimeofday(&time, NULL);
	ll_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	int_time = ll_time / 100;
	return (int_time);
}
