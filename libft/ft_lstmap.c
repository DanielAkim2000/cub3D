/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:34:35 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:36:11 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstclear_moded(t_list **lst, void (*del)(void *))
{
	t_list	*begin;
	t_list	*curr;
	t_list	*next;

	if (!lst || !del || !*lst)
		return (NULL);
	begin = *lst;
	curr = begin;
	while (curr)
	{
		next = curr->next;
		del(curr->content);
		free(curr);
		curr = next;
	}
	*lst = NULL;
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*begin_new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	begin_new = new;
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
			return (ft_lstclear_moded(&begin_new, del));
		ft_lstadd_back(&begin_new, temp);
		lst = lst->next;
	}
	return (begin_new);
}
