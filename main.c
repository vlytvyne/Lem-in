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
	room->visit_id = 0;
	room->id = 0;
	room->ancestor = NULL;
	i = 0;
	if (lines[1][0] == '-')
		i++;
	while (lines[1][i])
		if (!ft_isdigit(lines[1][i++]))
			error_exit("Please, enter rooms in the acceptable format.");
	i = 0;
	if (lines[2][0] == '-')
		i++;
	while (lines[2][i])
		if (!ft_isdigit(lines[2][i++]))
			error_exit("Please, enter rooms in the acceptable format.");
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

	sp_m = NO_SP_MEAN;
	while (*list && LIST_LINE[0] == '#')
	{
		if (ft_strequ("##start", LIST_LINE))
		{
			if (sp_m == END)
				error_exit("Two commands in the row.");
			if (start_found)
				error_exit("Two START command in the file.");
			sp_m = START;
			start_found++;
		}
		if (ft_strequ("##end", LIST_LINE))
		{
			if (sp_m == START)
				error_exit("Two commands in the row.");
			if (end_found)
				error_exit("Two END command in the file.");
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

int		extract_ants(t_list **list)
{
	int		ants;
	int		i;

	i = 0;
	while (*list && LIST_LINE[0] == '#')
	{
		if (ft_strequ("##start", LIST_LINE))
			error_exit("Start command doesn't work with ants.");
		if (ft_strequ("##end", LIST_LINE))
			error_exit("End command doesn't work with ants.");
		*list = (*list)->next;
	}
	if (*list)
	{
		while (LIST_LINE[i])
		{
			if (!ft_isdigit(LIST_LINE[i]))
				error_exit("Please, enter ants in the acceptable format.");
			i++;
		}
		ants = ft_atoi(LIST_LINE);
		if (ants == 0)
			error_exit("Please, enter ants in the acceptable format.");
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

void	link_rooms(t_list **list, t_r_list *rooms)
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
				return ;
			set_link(links, rooms);
			*list = (*list)->next;
		}
	}
}

t_room	*get_graph_end(t_r_list *rooms)
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
		error_exit("No start.");
	if (end == NULL)
		error_exit("No end.");
	return (end);
}

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
	//free(to_free);
	return (room);
}

int		mark_path(t_room *room)
{
	room->id = room->visit_id;
	room->visit_id = USED;
	if (room->sp_mean == END)
		return (0);
	if (room->ancestor)
	{
		room->distance = mark_path(room->ancestor) + 1;
	}
	return (room->distance);
}

t_room	*bfs(t_room *end, int visit_id)
{
	t_r_list	*front;
	t_r_list	*rear;
	t_room		*room;
	t_r_list	*adjacent;

	front = NULL;
	rear = NULL;
	enq(&rear, &front, end);
	while (front != NULL)
	{
		room = deq(&front);
		room->visit_id = visit_id;
		if (room->sp_mean == START)
		{
			mark_path(room->ancestor);
			return (room->ancestor);
		}
		adjacent = room->adjacent;
		while (adjacent)
		{
			if (adjacent->room->visit_id != visit_id && adjacent->room->visit_id != USED)
			{
				adjacent->room->ancestor = room;
				adjacent->room->visit_id = visit_id;
				enq(&rear, &front, adjacent->room);
			}
			adjacent = adjacent->next;
		}
	}
	return (NULL);
}

t_r_list	*get_paths(t_room *end)
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
			printf("L%i-%s ", room->ant, room->name);
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
	//printf("SUM: %i PATH: %i DI: %i\n", sum, path->distance, dist[i]);
		i++;
	}
	return (ants > sum);
}

void	print_dist(int *dist, t_r_list *paths)
{
	while (paths)
	{
		printf("DIST: %i\n", dist[paths->room->id]);
		paths = paths->next;
	}
}

void	print_pathes(t_r_list *paths)
{
	while (paths)
	{
		print_path(paths->room);
		paths = paths->next;
	}
	printf("\n");
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
	//print_dist(dist, paths);
	while (ant_name <= ants)
	{
		paths = start;
		path = paths->room;
		push_ants(path);
		path->ant = ant_name;
		paths = paths->next;
		while (paths && should_use_path(dist, paths->room, ants - ant_name))
		{
			ant_name++;
			path = paths->room;
			push_ants(path);
			path->ant = ant_name;
			paths = paths->next;
		}
		print_pathes(start);
		ant_name++;
	}
	// while (push_ants(path))
	// 	print_path(path);
}

int		main(void)
{
	t_list		*list;
	t_list		*list_start;
	int			ants;
	t_r_list	*rooms;
	t_room		*end;
	t_r_list	*paths;

	list = read_input();
	if (list == NULL)
		error_exit("Listen... You gotta input something...");
	list_start = list;
	ants = extract_ants(&list);
	rooms = create_rooms(&list);
	link_rooms(&list, rooms);
	end = get_graph_end(rooms);
	paths = get_paths(end);
	if (paths == NULL)
		error_exit("No path.");
	launch_ants(ants, paths);
	// while (rooms)
	// {
	// 	printf("ROOM: %s LINKS: ", rooms->room->name);
	// 	while (rooms->room->adjacent)
	// 	{
	// 		printf("|%s|", rooms->room->adjacent->room->name);
	// 		rooms->room->adjacent = rooms->room->adjacent->next;
	// 	}
	// 	printf("\n");
	// 	rooms = rooms->next;
	// }
//	ft_lstdel(&list_start, del_list);
//	system("leaks lem-in");
}