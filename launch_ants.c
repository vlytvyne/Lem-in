/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:35:26 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 13:36:24 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		push_ants(t_room *room)
{
	int		pushed;

	pushed = 0;
	while (room->NEXT)
	{
		if (room->ant != 0)
		{
			pushed = 1;
			if (room->NEXT->ant != 0)
				push_ants(room->NEXT);
			room->NEXT->ant = room->ant;
			room->ant = 0;
			return (1);
		}
		room = room->NEXT;
	}
	return (pushed);
}

void	print_path(t_room *room)
{
	while (room)
	{
		if (room->ant != 0)
			ft_printf("L%i-%s ", room->ant, room->name);
		if (room->sp_mean == END)
			room->ant = 0;
		room = room->NEXT;
	}
}

void	fill_dist(int *dist, t_r_list *paths)
{
	while (paths)
	{
		dist[paths->room->id] = paths->room->distance;
		paths = paths->next;
	}
}

int		should_use_path(int *dist, t_room *path, int ants)
{
	int		i;
	int		sum;

	i = 1;
	sum = 0;
	while (i < path->id)
	{
		sum += path->distance - dist[i];
		i++;
	}
	return (ants > sum);
}

void	launch_ants(int ants, t_r_list *paths)
{
	int 		ant_name;
	t_room		*path;
	int			dist[1000];
	t_r_list	*start;

	start = paths;
	ant_name = 1;
	fill_dist(dist, paths);
	while (ant_name <= ants)
	{
		paths = start;
		path = paths->room;
		push_ants(path);
		path->ant = ant_name;
		print_path(path);
		paths = paths->next;
		while (paths && should_use_path(dist, paths->room, ants - ant_name))
		{
			ant_name++;
			path = paths->room;
			push_ants(path);
			path->ant = ant_name;
			print_path(path);
			paths = paths->next;
		}
		while (paths && push_ants(paths->room))
		{
			print_path(paths->room);
			paths = paths->next;
		}
		ft_printf("\n");
		ant_name++;
	}
	int 	pushed = 1;
	while (pushed)
	{
		paths = start;
		pushed = 0;
		while (paths)
		{
			if (push_ants(paths->room))
			{
				pushed = 1;
				print_path(paths->room);
			}
			paths = paths->next;
		}
		if (pushed)
			ft_printf("\n");
	}
}
