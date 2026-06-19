/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 00:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/06/20 04:17:53 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* 数値・カンマの妥当性検証と atof 変換 */

int	is_valid_float(char *str)
{
	int	i;
	int	dot;

	if (!str || !*str)
		return (FAILURE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || (str[i] == '.' && str[i + 1] == '\0'))
		return (FAILURE);
	dot = 0;
	while (str[i])
	{
		if (str[i] == '.' && !dot)
			dot = 1;
		else if (!ft_isdigit(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

double	parse_atof(char *str, int *error)
{
	if (is_valid_float(str) != SUCCESS)
	{
		*error = FAILURE;
		return (0.0);
	}
	*error = SUCCESS;
	return (ft_atof(str));
}

// カンマは２個だけ。
bool	is_valid_comma(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!str[i] || str[i] == ',')
		return (false);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] == ',' || str[i + 1] == '\0')
				return (false);
			count++;
		}
		i++;
	}
	return (count == 2);
}
