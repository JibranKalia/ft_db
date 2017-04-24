/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:56:09 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 22:58:31 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		main(int argc, char **argv)
{
	t_client	*client;
	
//	ht_test();
	client = db_client_init();
	db_msg(MSG_WELCOME);
	db_loop(client);
}
