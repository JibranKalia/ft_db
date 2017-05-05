/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:58:04 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 15:27:36 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_search(t_server *server)
{
	t_db_file	**tmp;
	int		i;

	i = 0;
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		if (strcasestr(strchr(tmp[i]->value,':'), server->args[1]))
			REPLY(db_printer(tmp[i]->value));
		i++;
	}
	return (0);
}

int			db_getval(t_server *server)
{
	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 2, REPLY("usage: GETVAL VALUE"), 0);
	CHK(db_getfiles(server) == -1, -1);
	CHK(db_search(server) == -1, -1);
	return (0);
}
