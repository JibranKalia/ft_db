/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:52:14 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/22 16:57:58 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void	*ft_realloc(void *src, size_t srcsize, size_t newsize)
{
	void	*res;
	size_t	cpylen;

	cpylen = (srcsize < newsize) ? srcsize : newsize;
	CHK(!src, 0);
	CHK((res = ft_memalloc(newsize)) == 0, 0);
	ft_memcpy(res, src, cpylen);
	free(src);
	return (res);
}
