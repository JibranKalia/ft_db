/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 21:19:56 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		db_set(t_client *client)
{
	uint32_t	key;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 3, printf("usage: SET key value\n"), 0);
	if (client->hashsize == 0)
		client->hashsize = PROTO_HASH_SIZE;
	key = db_gethash(client, client->args[1]);
	printf("Hash = %d\n", key);
	return (0);
}

int		db_get(t_client *client)
{
	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->argc != 2, printf("usage: GET key\n"), 0);
	printf("DB_GET Num of Args: %d\n", client->argc);
	return (1);
}
