/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 20:37:15 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/23 20:45:35 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strnjoinf(char *src1, size_t len1, char const *src2, size_t len2)
{
	char *ret;

	CHK(src1 == 0 || src2 == 0, 0);
	CHK((ret = ft_strnew(len1 + len2)) == 0, NULL);
	ft_memcpy(ret, src1, len1);
	ft_memcpy(ret + len1, src2, len2);
	free(src1);
	return (ret);
}
