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
	VISITED,
	NOT_VIS,
	START,
	END
}					sp_mean;

typedef struct s_room t_room;

typedef struct		s_adjacent
{
	t_room			*room;
	t_room			*next;
}					t_adjacent;

typedef	struct		s_room
{
	char			*name;
	t_coor			coor;
	sp_mean			sp_mean;
	int				distance;
//	int				ants_wait;
	t_adjacent		*adjacent;
}					t_room;

#endif
