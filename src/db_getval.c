/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:58:04 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 22:45:45 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		db_getval(t_server *server)
{
	char	*buf;
	char	*out;
	char	*parsed;
	int	idx;

	(void)out;
	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 2, REPLY("usage: GETVAL VALUE"), 0);
	CHK(db_getfiles(server) == -1, -1);
	buf = db_catvalue(server);
	out = strstr(buf, server->args[1]);
	if (out == NULL)
	{
		REPLY("Value Not Found\n");
		return (0);
	}
	idx = out - buf;
	while (idx > 0)
	{
		if (buf[idx] == '\n')
		{
			break;
		}
		--idx;
	}
	while (*out)
	{
		if (*out == ',' || *out == '\n')
		{
			*out = 0;
			break;
		}
		++out;
	}
	parsed = db_printer(&buf[idx]);
	printf("%s\n", parsed);
	free(buf);
	return (0);
}
