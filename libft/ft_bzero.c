/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:28:44 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/10/25 14:32:35 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	char		*bytes;
	size_t		i;

	if (s == NULL)
		return ;
	bytes = (char*)s;
	i = 0;
	while (i < n)
		bytes[i++] = 0;
}
