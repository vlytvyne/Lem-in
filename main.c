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

t_room	*create_rooms(t_list **list)
{

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
	while (((char*)((*list)->content))[0] == '#')
	{
		if (ft_strequ("##start", ((char*)((*list)->content))))
			error("Start command doesn't work with ants.");
		if (ft_strequ("##end", ((char*)((*list)->content))))
			error("End command doesn't work with ants.");
		*list = (*list)->next;
	}
	while (((char*)((*list)->content))[i])
	{
		if (!ft_isdigit(((char*)((*list)->content))[i]))
			error("No no no, this is not gonna work, please, enter ants in the acceptable format.");
		i++;
	}
	ants = ft_atoi((char*)((*list)->content));
	if (ants == 0)
		error("Zero ants doesn't have any sense! Jesus...");
	else
		*list = (*list)->next;
	return (ants);
}

int		main(void)
{
	t_list	*list;
	t_list	*head;
	int		ants;

	list = read_input();
	head = list;
	ants = extract_ants(&list);
	while (list)
	{
		printf("%s\n", (char*)list->content);
		list = list->next;
	}
	ft_lstdel(&head, del_list);
//	system("leaks lem-in");
}