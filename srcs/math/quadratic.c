/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:15 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/13 12:07:55 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

double	quadratic_discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

/* 
this func return min solution of quadratic. 
if solution cant found or smaller than zero, 
basically return ERRORNO (-1),
but if a == 0 or discriminant == 0
it may return minus value other than ERRORNO.
*/

double	quadratic_min_solutoin(double a, double b, double c)
{
	double d;
	double n1;
	double n2;
	
	if (a == 0)
		return (-c / b);
	d = quadratic_discriminant(a, b, c);
	if (d < -EPS)
		return (ERRORNO);
	else if (d < EPS)
		return (-b / (2 * a));
	n1 = (-b - sqrt(d)) / (2 * a);
	n2 = (-b + sqrt(d)) / (2 * a);
	if (n1 < 0 && n2 < 0)
		return (ERRORNO);
	else if (n1 < 0 || n2 < n1)
		return (n2);
	else if (n2 < 0 || n1 < n2)
		return (n1);
	return (ERRORNO);
}

int main(int argc, char **argv)
{
	double a;
	double b;
	double c;
	double s;

	if (argc != 4)
		return (ft_dprintf(2, "ERROR!\n"), EXIT_FAILURE);
	a = ft_atoi(argv[1]);
	b = ft_atoi(argv[2]);
	c = ft_atoi(argv[3]);
	s = quadratic_min_solutoin(a, b, c);
	printf("quadratic_min_solutoin: %f\n", s);
	return (EXIT_SUCCESS);
}
