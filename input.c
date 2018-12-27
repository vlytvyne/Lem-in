/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:12:52 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 14:06:08 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

void	print_input(t_list *list)
{
	while (list)
	{
		ft_printf("%s\n", (char*)list->content);
		list = list->next;
	}
	ft_printf("\n");
}
