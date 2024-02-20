/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 16:41:14 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/23 16:41:14 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = ft_lstnew((f)(lst->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
		temp = temp->next;
	}
	return (new);
}
