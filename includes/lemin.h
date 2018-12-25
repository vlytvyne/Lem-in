/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:53:58 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/17 18:54:00 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft.h"
#include "printf.h"
#include "get_next_line.h"

#define LIST_LINE ((char*)((*list)->content))
#define USED INT_MAX
#define NEXT ancestor

typedef enum		e_sp_meaning
{
	NO_SP_MEAN,
	START,
	END
}					e_sp_mean;

typedef struct s_room t_room;

typedef struct		s_r_list
{
	t_room			*room;
	struct s_r_list	*next;
}					t_r_list;

typedef	struct		s_room
{
	char			*name;
	t_coor			coor;
	t_room			*ancestor;
	e_sp_mean		sp_mean;
	int				distance;
	int				ant;
	t_r_list		*adjacent;
	int				visit_id;
}					t_room;

#endif
