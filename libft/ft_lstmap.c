/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:29:13 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/17 16:40:21 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*tempret;
	t_list	*ret;

	if (!lst || !f)
		return (NULL);
	temp = f(lst);
	tempret = ft_lstnew(temp->content, temp->content_size);
	if (!tempret)
		return (NULL);
	ret = tempret;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		tempret->next = ft_lstnew(temp->content, temp->content_size);
		if (!tempret->next)
			return (NULL);
		lst = lst->next;
		tempret = tempret->next;
	}
	free(temp);
	free(tempret);
	return (ret);
}
