/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:29:36 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:20:06 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ret;

	if (!lst)
		return (NULL);
	if (lst->next == NULL)
	{
		ret = lst;
		return (ret);
	}
	ret = lst;
	while (ret->next)
		ret = ret->next;
	return (ret);
}
