/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:29:54 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:06:45 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	set_link(char **links, t_r_list *rooms)
{
	t_room	*room1;
	t_room	*room2;

	room1 = NULL;
	room2 = NULL;
	while (rooms)
	{
		if (ft_strequ(links[0], rooms->room->name))
			room1 = rooms->room;
		if (ft_strequ(links[1], rooms->room->name))
			room2 = rooms->room;
		rooms = rooms->next;
	}
	if (room1 == NULL || room2 == NULL)
		error_exit("Linking nonexistent room.");
	if (room1->adjacent == NULL)
		room1->adjacent = create_r_list(room2);
	else
		add_room_nocheck(room1->adjacent, create_r_list(room2));
	if (room2->adjacent == NULL)
		room2->adjacent = create_r_list(room1);
	else
		add_room_nocheck(room2->adjacent, create_r_list(room1));
}

void		link_rooms(t_list **list, t_r_list *rooms)
{
	char	**links;

	while (*list)
	{
		while (*list && LIST_LINE[0] == '#')
		{
			if (ft_strequ("##start", LIST_LINE))
				error_exit("Start command doesn't work with links.");
			if (ft_strequ("##end", LIST_LINE))
				error_exit("End command doesn't work with links.");
			*list = (*list)->next;
		}
		if (*list)
		{
			links = ft_strsplit(LIST_LINE, '-');
			if (count_words(links) != 2)
			{
				free_after_split(links);
				return ;
			}
			set_link(links, rooms);
			free_after_split(links);
			*list = (*list)->next;
		}
	}
}
