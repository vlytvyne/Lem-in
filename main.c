/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:52:31 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 19:39:49 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN_FILE
#include "lemin.h"

void	show_usage(void)
{
	ft_printf("usage: ./lem-in [-vsnch] < map\n");
	ft_printf("       -h    help     - show usage.\n");
	ft_printf("       -v    verbose  - show found path and number of lines ");
	ft_printf("at the end of output.\n");
	ft_printf("       -s    silent   - don't show map.\n");
	ft_printf("       -v    color    - assign to each ant a color.\n");
	ft_printf("       -n    name     - add ants some individuality.\n");
	exit(0);
}

void	remember_flag(char ch)
{
	if (ch == 'v')
		g_flags.verbose = 1;
	else if (ch == 's')
		g_flags.silent = 1;
	else if (ch == 'n')
		g_flags.names = 1;
	else if (ch == 'c')
		g_flags.color = 1;
	else
		show_usage();
}

void	read_flags(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	g_flags = (t_flags){0, 0, 0, 0};
	if (argc == 1)
		return ;
	while (i < argc)
	{
		j = 1;
		if (argv[i][0] != '-')
			show_usage();
		while (argv[i][j])
		{
			remember_flag(argv[i][j]);
			j++;
		}
		i++;
	}
}

void	print_verbose(t_r_list *paths)
{
	t_room	*path;
	int		ft;

	ft_printf("%t\n", B_MAGENTA);
	while (paths)
	{
		ft = 1;
		path = paths->room;
		ft_printf("Path number: %2i Distance: %3i | ", path->id,
		path->distance);
		while (path)
		{
			if (ft)
			{
				ft_printf("%s", path->name);
				ft = 0;
			}
			else
				ft_printf(" -> %s", path->name);
			path = path->NEXT;
		}
		ft_putstr("\n-----------------------------------------\n");
		paths = paths->next;
	}
	ft_printf("%tLines: %i\n", B_GREEN, g_lines);
}

int		main(int argc, char **argv)
{
	t_list		*list;
	t_list		*list_start;
	int			ants;
	t_r_list	*rooms;
	t_r_list	*paths;

	g_lines = 0;
	read_flags(argc, argv);
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
	if (!g_flags.silent)
		print_input(list_start, list);
	launch_ants(ants, paths, get_dist(paths));
	if (g_flags.verbose)
		print_verbose(paths);
}
