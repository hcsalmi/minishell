/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:54:13 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/12 16:26:09 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*temp_lst;

	temp_lst = lst;
	if (!lst || !f)
		return ;
	while (temp_lst)
	{
		(*f)(temp_lst);
		temp_lst = temp_lst->next;
	}
}
