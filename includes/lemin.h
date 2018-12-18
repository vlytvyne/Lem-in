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

typedef enum		e_sp_meaning
{
	NO_SPEC,
	START,
	END
}					sp_mean;

typedef struct		s_neighbors
{
	t_room			*room;
	t_room			*next;
}					t_neighbors;

typedef	struct		s_room
{
	char			*name;
	t_coor			coor;
	sp_mean			sp_mean;
	int				distance;
//	int				ants_wait;
	t_neighbors		*descendants;
	struct s_room	*ancestor;
}					t_room;

#endif
