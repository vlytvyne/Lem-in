/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:05:53 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:07:04 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	enq(t_r_list **rear, t_r_list **front, t_room *room)
{
	t_r_list	*curr;

	curr = create_r_list(room);
	if (*rear != NULL)
		(*rear)->next = curr;
	*rear = curr;
	if (*front == NULL)
		*front = curr;
}

t_room	*deq(t_r_list **front)
{
	t_r_list	*to_free;
	t_room		*room;

	if (*front == NULL)
		return (NULL);
	to_free = *front;
	room = (*front)->room;
	*front = (*front)->next;
	return (room);
}

void	free_que(t_r_list *front)
{
	t_r_list *to_free;

	while (front)
	{
		to_free = front;
		front = front->next;
		free(to_free);
	}
}
