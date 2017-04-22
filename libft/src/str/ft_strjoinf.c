/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 20:37:15 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 13:21:05 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strjoinf(char *src1, char *src2, int d)
{
	char	*ret;
	char	*dst;
	char	*s1;
	char	*s2;
	size_t	len;

	s1 = src1;
	s2 = src2;
	CHK(src1 == 0 || src2 == 0, 0);
	CHK(d == 0, 0);
	len = ft_strlen(src1);
	len += ft_strlen(src2);
	CHK((dst = ft_strnew(len + 1)) == 0, NULL);
	ret = dst;
	while (*src1)
		*dst++ = *src1++;
	while (*src2)
		*dst++ = *src2++;
	*dst = '\0';
	if (d == 1)
		free(s1);
	else if (d == 2)
		free(s2);
	else if (d == 3)
	{
		free(s1);
		free(s2);
	}
	return (ret);
}
