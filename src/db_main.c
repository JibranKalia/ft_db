/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:36:35 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 21:53:08 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	start()
{
	int		ret;

	printf("Enter number to select option\n1.\tCreate New DB\n2.\tLoad Existing DB\n3.\tExit.\n");
	scanf("%d", &ret);
	if (ret == 1)
		db_create();
	else if (ret == 2)
		db_load();
	else if (ret == 3)
		exit(1);
	else
	{
		printf("Enter a number between 1 and 3\n");
		start();
	}
}

int main(void)
{
	start();
	return (0);
}
