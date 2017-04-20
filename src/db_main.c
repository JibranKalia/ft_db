/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:36:35 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 18:12:28 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int main(void)
{
	int		ret;

	printf("Enter number to select option\n1.\tCreate New DB\n2.\tLoad Existing DB\n3.\tExit.\n");
	scanf("%d", &ret);
	if (ret == 1)
		db_create();
	return (0);
}
