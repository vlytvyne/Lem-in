/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:23:39 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:36:27 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		mark_path(t_room *room)
{
	room->id = room->visit_id;
	room->visit_id = USED;
	if (room->sp_mean == END)
		return (1);
	if (room->ancestor)
	{
		room->distance = mark_path(room->ancestor) + 1;
	}
	return (room->distance);
}

static void		put_to_que(t_room *room, t_r_list **front,
							t_r_list **rear, int visit_id)
{
	t_r_list	*adjacent;

	adjacent = room->adjacent;
	while (adjacent)
	{
		if (adjacent->room->visit_id != visit_id &&
			adjacent->room->visit_id != USED)
		{
			adjacent->room->ancestor = room;
			adjacent->room->visit_id = visit_id;
			enq(rear, front, adjacent->room);
		}
		adjacent = adjacent->next;
	}
}

static t_room	*bfs(t_room *end, int visit_id)
{
	t_r_list	*front;
	t_r_list	*rear;
	t_r_list	*start;
	t_room		*room;

	front = NULL;
	rear = NULL;
	enq(&rear, &front, end);
	start = front;
	while (front != NULL)
	{
		room = deq(&front);
		room->visit_id = visit_id;
		if (room->sp_mean == START)
		{
			mark_path(room->ancestor);
			free_que(start);
			return (room->ancestor);
		}
		put_to_que(room, &front, &rear, visit_id);
	}
	free_que(start);
	return (NULL);
}

t_r_list		*get_paths(t_room *end)
{
	int			i;
	t_room		*path;
	t_r_list	*paths;

	i = 1;
	paths = NULL;
	while ((path = bfs(end, i)))
	{
		if (paths == NULL)
			paths = create_r_list(path);
		else
			add_room_nocheck(paths, create_r_list(path));
		if (path->sp_mean == END)
			break ;
		i++;
	}
	return (paths);
}
