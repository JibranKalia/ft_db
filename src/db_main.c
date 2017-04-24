/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:56:09 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 23:12:57 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		main(void)
{
	t_client	*client;
	
	client = db_client_init();
	db_msg(MSG_WELCOME);
	db_loop(client);
}
