/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:15 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/14 09:01:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

double	quad_discriminant(double a, double b, double c)
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

double	quad_min_solutoin(double a, double b, double c)
{
	double d;
	double n1;
	double n2;
	
	if (a == 0 && b == 0)
		return (ERRORNO);
	if (a == 0)
		return (-c / b);
	d = quad_discriminant(a, b, c);
	if (d < -EPS)
		return (ERRORNO);
	else if (d < EPS)
		return (-b / (2 * a));
	n1 = (-b - sqrt(d)) / (2 * a);
	n2 = (-b + sqrt(d)) / (2 * a);
	return (min_double(n1, n2));
}

double	min_double(double d1, double d2)
{
	if (d1 < 0 && d2 < 0)
		return (ERRORNO);
	else if (d1 < 0)
		return (d2);
	else if (d2 < 0)
		return (d1);
	else if (d1 < d2)
		return (d1);
	return (d2);
}

/* 
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
 */
