/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:28:59 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/14 17:13:23 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

double	ft_atof(const char *nptr)
{
	const char	*ptr;
	double		result;
	double		scale;

	ptr = ft_strchr(nptr, '.');
	result = (double)ft_atoi(nptr);
	if (!ptr)
		return (result);
	nptr += (int)(ptr - nptr) + 1;
	scale = 0.1;
	while (*nptr)
	{
		result += (scale * (double)(*nptr - '0'));
		scale /= 10;
		nptr++;
	}
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%.4f\n", ft_atof("14.2455"));
// 	// printf("%.5f\n", ft_atof("14.2455"));
// 	// printf("%.5f\n", ft_atof("14.2455"));
// 	// printf("%.5f\n", (double)14.0 / (double)0.1);
// 	// printf("%.5f\n", (double)0.1 / 10);

// }
