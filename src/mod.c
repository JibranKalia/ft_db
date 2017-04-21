/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:17:31 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/21 13:15:43 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
char	ft_puthex(char c)
{
	char tab[16] = "0123456789abcdef";

	return (tab[c % 16]);
}

char	*hash(char *str)
{
	char *res;
	int		i = 0;
	int		len = 4;

	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	while(i < len && str[i])
	{
		res[i] = ft_puthex(str[i]);
		i++;
	}
	while (i < len)
	{
		res[i] = '0';
		i++;
	}
	return (res);
}

int 	main(void)
{
	char	*str;
	char	**all;
	char	*temp;
	char 	*st;

	str = "Bob, Johnson, 28, Engineer";
	all = ft_strsplit(str, ',');
	st = "\0";
	while(*all)
	{
		temp = hash(*all);
		st = ft_strjoin(st, temp);
		all++;
	}
	printf("%s\n", st);
	return (0);
}
