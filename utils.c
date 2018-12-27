/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:14:51 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:08:00 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			count_words(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

void		free_after_split(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

t_r_list	*create_r_list(t_room *room)
{
	t_r_list *list;

	list = (t_r_list*)malloc(sizeof(t_r_list));
	list->room = room;
	list->next = NULL;
	return (list);
}

void		add_room_nocheck(t_r_list *head, t_r_list *new)
{
	if (head == NULL || new == NULL)
		return ;
	while (head->next)
		head = head->next;
	head->next = new;
}

void		add_room(t_r_list *head, t_r_list *new)
{
	if (head == NULL || new == NULL)
		return ;
	while (head->next)
	{
		if (head->room->coor.x == new->room->coor.x &&
			head->room->coor.y == new->room->coor.y)
			error_exit("Different rooms have same coordinates.");
		if (ft_strequ(head->room->name, new->room->name))
			error_exit("Different rooms have same names.");
		head = head->next;
	}
	if (head->room->coor.x == new->room->coor.x &&
		head->room->coor.y == new->room->coor.y)
		error_exit("Different rooms have same coordinates.");
	if (ft_strequ(head->room->name, new->room->name))
		error_exit("Different rooms have same names.");
	head->next = new;
}
