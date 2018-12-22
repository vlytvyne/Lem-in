/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:52:31 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/17 18:52:44 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
# include <stdio.h>

t_list	*read_input(void)
{
	t_list	*head;
	t_list	*prev;
	t_list	*list;
	char	*line;

	head = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (head == NULL)
		{
			head = (t_list*)malloc(sizeof(t_list));
			head->next = NULL;
			head->content = line;
			prev = head;
		}
		else
		{
			list = (t_list*)malloc(sizeof(t_list));
			list->next = NULL;
			list->content = line;
			prev->next = list;
			prev = list;
		}
	}
	return (head);
}

void	add_room_nocheck(t_r_list *head, t_r_list *new)
{
	if (head == NULL || new == NULL)
		return ;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	add_room(t_r_list *head, t_r_list *new)
{
	if (head == NULL || new == NULL)
		return ;
	while (head->next)
	{
		if (head->room->coor.x == new->room->coor.x &&
			head->room->coor.y == new->room->coor.y)
			error("Different rooms have same coordinates.");
		if (ft_strequ(head->room->name, new->room->name))
			error("Different rooms have same names.");
		head = head->next;
	}
	if (head->room->coor.x == new->room->coor.x &&
		head->room->coor.y == new->room->coor.y)
		error("Different rooms have same coordinates.");
	if (ft_strequ(head->room->name, new->room->name))
		error("Different rooms have same names.");
	head->next = new;
}

t_r_list	*create_r_list(t_room *room)
{
	t_r_list *list;

	list = (t_r_list*)malloc(sizeof(t_r_list));
	list->room = room;
	list->next = NULL;
	return (list);
}

//проверять начинаеться ли комната с 'L'
t_room		*init_room(char	**lines, e_sp_mean sp_mean)
{
	t_room	*room;
	int		i;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = lines[0];
	room->distance = INT_MAX / 2;
	room->sp_mean = sp_mean;
	if (sp_mean == END)
		room->distance = 0;
	room->adjacent = NULL;
	room->ant = 0;
	i = 0;
	if (lines[1][0] == '-')
		i++;
	while (lines[1][i])
		if (!ft_isdigit(lines[1][i++]))
			error("Please, enter rooms in the acceptable format.");
	i = 0;
	if (lines[2][0] == '-')
		i++;
	while (lines[2][i])
		if (!ft_isdigit(lines[2][i++]))
			error("Please, enter rooms in the acceptable format.");
	room->coor.x = ft_atoi(lines[1]);
	room->coor.y = ft_atoi(lines[2]);
	return (room);
}

int			count_words(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

e_sp_mean	process_commands(t_list **list)
{
	e_sp_mean	sp_m;
	static int	start_found = 0;
	static int	end_found = 0;

	sp_m = NOT_VIS;
	while (*list && LIST_LINE[0] == '#')
	{
		if (ft_strequ("##start", LIST_LINE))
		{
			if (sp_m == END)
				error("Two commands in the row.");
			if (start_found)
				error("Two START command in the file.");
			sp_m = START;
			start_found++;
		}
		if (ft_strequ("##end", LIST_LINE))
		{
			if (sp_m == START)
				error("Two commands in the row.");
			if (end_found)
				error("Two END command in the file.");
			sp_m = END;
			end_found++;
		}
		*list = (*list)->next;
	}
	return (sp_m);
}

t_r_list	*create_rooms(t_list **list)
{
	char		**lines;
	t_r_list	*rooms;
	e_sp_mean	sp_m;

	rooms = NULL;
	while (*list)
	{
		sp_m = process_commands(list);
		if (*list)
		{
			lines = ft_strsplit(LIST_LINE, ' ');
			if (count_words(lines) != 3)
				return (rooms);
			if (rooms == NULL)
				rooms = create_r_list(init_room(lines, sp_m));
			else
				add_room(rooms, create_r_list(init_room(lines, sp_m)));
			*list = (*list)->next;
		}
	}
	return (rooms);
}

void	del_list(void *content, size_t size)
{
	free(content);
}

int		extract_ants(t_list **list)
{
	int		ants;
	t_list	*to_free;
	int		i;

	i = 0;
	while (*list && LIST_LINE[0] == '#')
	{
		if (ft_strequ("##start", LIST_LINE))
			error("Start command doesn't work with ants.");
		if (ft_strequ("##end", LIST_LINE))
			error("End command doesn't work with ants.");
		*list = (*list)->next;
	}
	if (*list)
	{
		while (LIST_LINE[i])
		{
			if (!ft_isdigit(LIST_LINE[i]))
				error("Please, enter ants in the acceptable format.");
			i++;
		}
		ants = ft_atoi(LIST_LINE);
		if (ants == 0)
			error("Please, enter ants in the acceptable format.");
		else
			*list = (*list)->next;
	}
	return (ants);
}

void	set_link(char **links, t_r_list *rooms)
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
		error("Linking nonexistent room.");
	
	if (room1->adjacent == NULL)
		room1->adjacent = create_r_list(room2);
	else
		add_room_nocheck(room1->adjacent, create_r_list(room2));

	if (room2->adjacent == NULL)
		room2->adjacent = create_r_list(room1);
	else
		add_room_nocheck(room2->adjacent, create_r_list(room1));
}

void	link_rooms(t_list **list, t_r_list *rooms)
{
	char	**links;

	while (*list)
	{
		while (*list && LIST_LINE[0] == '#')
		{
			if (ft_strequ("##start", LIST_LINE))
				error("Start command doesn't work with links.");
			if (ft_strequ("##end", LIST_LINE))
				error("End command doesn't work with links.");
			*list = (*list)->next;
		}
		if (*list)
		{
			links = ft_strsplit(LIST_LINE, '-');
			if (count_words(links) != 2)
				return ;
			set_link(links, rooms);
			*list = (*list)->next;
		}
	}
}

t_room	*get_graph_start(t_r_list *rooms)
{
	t_room	*start;
	t_room	*end;

	start = NULL;
	end = NULL;
	while (rooms)
	{
		if (rooms->room->sp_mean == START)
			start = rooms->room;
		if (rooms->room->sp_mean == END)
			end = rooms->room;
		rooms = rooms->next;
	}
	if (start == NULL)
		error("No start.");
	if (end == NULL)
		error("No end.");
	return (start);
}

int		init_graph(t_room *graph)
{
	t_r_list	*rooms;
	int			distance;

	if (graph->sp_mean == END)
	{
		printf("END\n");
		return (0);
	}
	rooms = graph->adjacent;
	graph->sp_mean = VISITED;
	while (rooms)
	{
		if (rooms->room->sp_mean != VISITED)
		{
		// if (rooms->room->distance != INT_MAX / 2)
		//  	distance = rooms->room->distance + 1;
		// else
			distance = init_graph(rooms->room) + 1;
		}
		else
			distance = rooms->room->distance + 1;
		graph->distance = distance < graph->distance ? distance : graph->distance;
		rooms = rooms->next;
	}
	//graph->sp_mean = NOT_VIS;
	printf("NAME: %s DIS: %i\n", graph->name, graph->distance);
	return (graph->distance);
}

int		main(void)
{
	t_list		*list;
	t_list		*list_start;
	int			ants;
	t_r_list	*rooms;
	t_room		*graph;

	list = read_input();
	if (list == NULL)
		error("Listen... You gotta input something...");
	list_start = list;
	ants = extract_ants(&list);
	rooms = create_rooms(&list);
	link_rooms(&list, rooms);
	graph = get_graph_start(rooms);
	// while (list)
	// {
	// 	printf("%s\n", (char*)list->content);
	// 	list = list->next;
	// }
	printf("THE MOST SHORT PATH: %i\n", init_graph(graph));
	while (rooms)
	{
		printf("ROOM: %s DISTANCE: %i\n", rooms->room->name, rooms->room->distance);
		rooms = rooms->next;
	}
//	ft_lstdel(&list_start, del_list);
//	system("leaks lem-in");
}