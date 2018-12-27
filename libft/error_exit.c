/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:27:38 by vlytvyne          #+#    #+#             */
/*   Updated: 2018/12/20 18:31:08 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

void	error_exit(char *msg)
{
	ft_printf("%tERROR:%t %s\n", B_RED, EOC, msg);
	exit(errno);
}
