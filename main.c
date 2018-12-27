/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:52:31 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 15:19:41 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_list		*list;
	t_list		*list_start;
	int			ants;
	t_r_list	*rooms;
	t_r_list	*paths;

	list = read_input();
	if (list == NULL)
		error_exit("Listen... You gotta input something...");
	list_start = list;
	ants = extract_ants(&list);
	rooms = create_rooms(&list);
	link_rooms(&list, rooms);
	paths = get_paths(get_graph_end(rooms));
	if (paths == NULL)
		error_exit("No path.");
	print_input(list_start);
	launch_ants(ants, paths, get_dist(paths));
	system("leaks lem-in");
}
