/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:31:01 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/10 14:31:13 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

void	zero_vars(int howmuch, ...)
{
	va_list args;
	int		i;
	int		*int_adress;

	i = 0;
	va_start(args, howmuch);
	while (i < howmuch)
	{
		int_adress = va_arg(args, int *);
		*int_adress = 0;
		i++;
	}
	va_end(args);
}
