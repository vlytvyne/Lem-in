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
	char	*line;
	int		i;

	i = 0;
	head = NULL;
	int ret;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (head == NULL)
			head = ft_lstnew(line, ft_strlen(line) + 1);
		else
			lst_add_end(head, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	return (head);
}

int		main(void)
{
	t_list	*list = read_input();

	while (list)
	{
		printf("From list:%s\n", (char*)list->content);
		free(list->content);
		list = list->next;
	}
	//system("leaks lem-in");
}