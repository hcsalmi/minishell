/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:27:50 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/12 16:26:13 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*nextcontent;

	if (!alst || !del)
		return ;
	list = *alst;
	while (list->next != NULL)
	{
		nextcontent = list->next;
		del(list->content, list->content_size);
		free(list);
		list = nextcontent;
	}
	del(list->content, list->content_size);
	free(list);
	*alst = NULL;
}
