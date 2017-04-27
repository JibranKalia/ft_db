/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:20:07 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/26 17:28:25 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

t_server	*db_server_init(void)
{
	t_server	*server;

	server = (t_server *)ft_memalloc(sizeof(t_server));
	server->flag_db_load = false;
	server->flag_tbl_load = false;
	server->fd = STDOUT_FILENO;
	return (server);
}

void		db_server_clean(t_server *server)
{
	if (server == 0)
		return ;
	if (server->args)
		ft_tbldel(server->args);
	ft_strclr(server->line);
	ft_strclr(server->dbpath);
	ft_strclr(server->logpath);
}
