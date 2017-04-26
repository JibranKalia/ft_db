/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:19:59 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 14:37:08 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstfree(t_list **alst)
{
	t_list	*to_free;
	t_list	*tmp;

	tmp = *alst;
	to_free = *alst;

	if (!*alst)
		return ;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->content);
		to_free->content = NULL;
		free(to_free);
		to_free = NULL;
	}
	alst = NULL;
}
