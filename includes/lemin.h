/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:53:58 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/27 20:06:10 by vlytvyne         ###   ########.fr       */
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

typedef struct			s_flags
{
	unsigned int		verbose:1;
	unsigned int		silent:1;
	unsigned int		names:1;
	unsigned int		color:1;
}						t_flags;

#ifdef  MAIN_FILE
t_flags g_flags;
int		g_lines;
#else
extern t_flags	g_flags;
extern int		g_lines;
#endif

typedef enum			e_sp_meaning
{
	NO_SP_MEAN,
	START,
	END
}						e_sp_mean;

typedef struct s_room	t_room;

typedef struct			s_r_list
{
	t_room				*room;
	struct s_r_list		*next;
}						t_r_list;

typedef	struct			s_room
{
	char				*name;
	t_coor				coor;
	t_room				*ancestor;
	e_sp_mean			sp_mean;
	int					distance;
	int					ant;
	t_r_list			*adjacent;
	int					visit_id;
	int					id;
}						t_room;

void					enq(t_r_list **rear, t_r_list **front, t_room *room);
t_room					*deq(t_r_list **front);
void					free_que(t_r_list *front);
t_list					*read_input(void);
void					print_input(t_list *start, t_list *list);
int						count_words(char **lines);
void					free_after_split(char **lines);
t_r_list				*create_r_list(t_room *room);
void					add_room_nocheck(t_r_list *head, t_r_list *new);
void					add_room(t_r_list *head, t_r_list *new);
t_r_list				*get_paths(t_room *end);
t_r_list				*create_rooms(t_list **list);
void					link_rooms(t_list **list, t_r_list *rooms);
int						extract_ants(t_list **list);
t_room					*get_graph_end(t_r_list *rooms);
void					launch_ants(int ants, t_r_list *paths, int *dist);
int						*get_dist(t_r_list *paths);
void					print_path(t_room *room);
void					end_of_line(void);

#endif
