/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:11:52 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 01:39:27 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t				i;
	unsigned char		*p;

	p = ptr;
	i = 0;
	while (i < n)
		p[i++] = c;
	return (p);
}
