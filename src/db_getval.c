/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:58:04 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 13:08:51 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_search(t_server *server)
{
	char	*buf;
	char	*out;
	int		idx;

	buf = db_catvalue(server);
	out = strstr(buf, server->args[1]);
	CHK1(out == NULL, REPLY("Value Not Found"), 0);
	idx = out - buf;
	while (idx > 0)
	{
		if (buf[idx] == '\n')
			break ;
		--idx;
	}
	while (*out)
	{
		if (*out == ',' || *out == '\n')
		{
			*out = 0;
			break ;
		}
		++out;
	}
	REPLY(db_printer(&buf[idx]));
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
