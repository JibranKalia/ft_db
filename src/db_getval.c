/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:58:04 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 16:02:02 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_search(t_server *server)
{
	t_db_file	**tmp;
	int		len;
	int		i;
	char		buffer[BUFF_SIZE];

	i = 0;
	bzero(buffer, BUFF_SIZE);
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		if (strcasestr(strchr(tmp[i]->value,':'), server->args[1]))
		{
			strcat(buffer, db_printer(tmp[i]->value));
			strcat(buffer, "\n");
		}
		i++;
	}
	len = strlen(buffer);
	buffer[len - 1] = 0;
	REPLY(buffer);
	bzero(buffer, BUFF_SIZE);
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
