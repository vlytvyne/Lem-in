/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:35:26 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 15:32:10 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	push_ants(t_room *room)
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

static int	should_use_path(int *dist, t_room *path, int ants)
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

static void	all_ants_on_map(t_r_list *start)
{
	int			pushed;
	t_r_list	*paths;

	pushed = 1;
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

static void	load_push_print(t_r_list *paths, int ant_name)
{
	t_room		*path;

	path = paths->room;
	push_ants(path);
	path->ant = ant_name;
	print_path(path);
}

void		launch_ants(int ants, t_r_list *paths, int *dist)
{
	int			ant_name;
	t_r_list	*start;

	start = paths;
	ant_name = 0;
	while (++ant_name <= ants)
	{
		paths = start;
		load_push_print(paths, ant_name);
		paths = paths->next;
		while (paths && should_use_path(dist, paths->room, ants - ant_name))
		{
			ant_name++;
			load_push_print(paths, ant_name);
			paths = paths->next;
		}
		while (paths && push_ants(paths->room))
		{
			print_path(paths->room);
			paths = paths->next;
		}
		ft_printf("\n");
	}
	free(dist);
	all_ants_on_map(start);
}
