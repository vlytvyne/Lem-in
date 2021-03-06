/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:33:51 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 19:36:07 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	g_colors[6][9] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
char	g_names[30][100] = {"Богдана", "Петя", "Василь", "Ніколя", "Іван",
	"Пан мураха", "Сергій", "Богуслава", "Михайло", "Єгор", "Йосип",
	"Іванка", "Валера", "Даринка", "Гаврило", "Марися", "Супермураха",
	"Віталій Семенович", "Зоя", "Казимир", "Леонід", "Забава", "Бандерівець",
	"Ярик", "Кирило", "Ілля", "Ганна", "Микола", "Юлька", "Павло"};

void	check_commands(t_list **list)
{
	if (ft_strequ("##start", LIST_LINE))
		error_exit("Start command doesn't work with ants.");
	if (ft_strequ("##end", LIST_LINE))
		error_exit("End command doesn't work with ants.");
}

int		extract_ants(t_list **list)
{
	int		ants;
	int		i;

	i = 0;
	ants = 0;
	while (*list && LIST_LINE[0] == '#')
	{
		check_commands(list);
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
			error_exit("Zero ants doesn't have any sense.");
		else
			*list = (*list)->next;
	}
	return (ants);
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

int		*get_dist(t_r_list *paths)
{
	int		*dist;

	dist = (int*)malloc(sizeof(int) * 1000);
	while (paths)
	{
		dist[paths->room->id] = paths->room->distance;
		paths = paths->next;
	}
	return (dist);
}

void	print_path(t_room *room)
{
	while (room)
	{
		if (room->ant != 0)
		{
			if (g_flags.color)
				ft_printf("%t", g_colors[room->ant % 6]);
			if (g_flags.names)
				ft_printf("%s-%s ", g_names[room->ant % 30], room->name);
			else
				ft_printf("L%i-%s ", room->ant, room->name);
		}
		if (room->sp_mean == END)
			room->ant = 0;
		room = room->NEXT;
	}
}
