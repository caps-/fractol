/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:12:49 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/10 16:15:47 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Same as ft_putendl_fd I guess, but just writes to the standard output
 * instead of to a file descriptor.*/
void	ft_putendl(char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, ++s, 1);
	write(1, "\n", 1);
}
