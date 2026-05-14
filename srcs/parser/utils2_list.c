/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 01:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/14 23:45:42 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

/* 汎用 intrusive list 操作 (append, clear) */

void	list_append(void **head, void *node)
{
	void	*cur;

	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (*(void **)cur)
		cur = *(void **)cur;
	*(void **)cur = node;
}

void	list_clear(void **head)
{
	void	*cur;
	void	*nxt;

	cur = *head;
	while (cur)
	{
		nxt = *(void **)cur;
		free(cur);
		cur = nxt;
	}
	*head = NULL;
}
