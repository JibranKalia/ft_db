/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:19:59 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 14:25:56 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstfree(t_list **alst)
{
	t_list	*temp;

	temp = *alst;
	if (!*alst)
		return ;
	while(*alst)
	{
		temp = *alst;
		*alst = *(alst)->next;
		free(temp->content);
		temp->content = NULL;
		free(temp);
		temp = NULL;
	}
}
