/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:26:25 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:04:17 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room		*init_room(char **lines, e_sp_mean sp_mean)
{
	t_room	*room;
	int		i;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = lines[0];
	room->sp_mean = sp_mean;
	room->adjacent = NULL;
	room->ant = 0;
	room->visit_id = 0;
	room->ancestor = NULL;
	i = 0;
	while (lines[1][i])
		if (!ft_isdigit(lines[1][i++]))
			error_exit("Please, enter rooms in the acceptable format.");
	i = 0;
	while (lines[2][i])
		if (!ft_isdigit(lines[2][i++]))
			error_exit("Please, enter rooms in the acceptable format.");
	room->coor.x = ft_atoi(lines[1]);
	room->coor.y = ft_atoi(lines[2]);
	free(lines[1]);
	free(lines[2]);
	free(lines);
	return (room);
}

void				check_start(e_sp_mean sp_mean, int start_found)
{
	if (sp_mean == END)
		error_exit("Two commands in the row.");
	if (start_found)
		error_exit("Two START command in the file.");
}

void				check_end(e_sp_mean sp_mean, int end_found)
{
	if (sp_mean == START)
		error_exit("Two commands in the row.");
	if (end_found)
		error_exit("Two END command in the file.");
}

static e_sp_mean	process_commands(t_list **list)
{
	e_sp_mean	sp_mean;
	static int	start_found = 0;
	static int	end_found = 0;

	sp_mean = NO_SP_MEAN;
	while (*list && LIST_LINE[0] == '#')
	{
		if (ft_strequ("##start", LIST_LINE))
		{
			check_start(sp_mean, start_found);
			sp_mean = START;
			start_found++;
		}
		if (ft_strequ("##end", LIST_LINE))
		{
			check_end(sp_mean, end_found);
			sp_mean = END;
			end_found++;
		}
		*list = (*list)->next;
	}
	return (sp_mean);
}

t_r_list			*create_rooms(t_list **list)
{
	char		**lines;
	t_r_list	*rooms;
	e_sp_mean	sp_mean;

	rooms = NULL;
	while (*list)
	{
		sp_mean = process_commands(list);
		if (*list)
		{
			lines = ft_strsplit(LIST_LINE, ' ');
			if (count_words(lines) != 3)
			{
				free_after_split(lines);
				return (rooms);
			}
			if (rooms == NULL)
				rooms = create_r_list(init_room(lines, sp_mean));
			else
				add_room(rooms, create_r_list(init_room(lines, sp_mean)));
			*list = (*list)->next;
		}
	}
	return (rooms);
}
