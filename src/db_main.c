/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:36:35 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/21 13:47:00 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

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

int main(int argc, char **argv)
{
	t_hashtable *hash;

	hash = ht_create(65536);

	ht_set(hash, "key1", "inky");
	ht_set(hash, "key2", "pinky");
	ht_set(hash, "key3", "blinky");
	ht_set(hash, "key4", "floyd");

	printf("%s\n", ht_get(hash, "key1"));
	printf("%s\n", ht_get(hash, "key2"));
	printf("%s\n", ht_get(hash, "key3"));
	printf("%s\n", ht_get(hash, "key4"));

	return 0;
}
