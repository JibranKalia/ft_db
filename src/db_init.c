/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:20:07 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 17:25:21 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

t_client	*db_client_init(void)
{
	t_client	*client;

	client = (t_client *)ft_memalloc(sizeof(t_client));
	client->flag_db_load = false;
	client->flag_tbl_load = false;
	return (client);
}

void		db_client_clean(t_client *client)
{
	if (client == 0)
		return ;
	if (client->args)
		ft_tbldel(client->args);
	ft_strclr(client->line);
	ft_strclr(client->dbpath);
	ft_strclr(client->logpath);
}
