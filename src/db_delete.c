/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/26 20:03:55 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_deletetbl(t_server *server)
{
	char	*buf;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	buf = ft_strjoin("rm -rf ", server->tblpath);
	db_reply(server, "Removing: %s\n", server->tblpath);
	system(buf);
	server->flag_tbl_load = false;
	free(buf);
	return (0);
}

static int	db_deletedb(t_server *server)
{
	char	*buf;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	buf = ft_strjoin("rm -rf ", server->dbpath);
	db_reply(server, "Removing: %s\n", server->dbpath);
	system(buf);
	server->flag_db_load = false;
	free(buf);
	return (0);
}

int		db_deletekey(t_server *server)
{
	char	*filename;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, db_msg(server, MSG_DELETE_USAGE2), 0);
	filename = ft_strjoinf("/", db_gethash(server, server->args[2]), STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(server->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2(remove(filename) == -1, free(filename), perror("REMOVE ERROR"), -1);
	db_reply(server, "Removing: %s\n", filename);
	free(filename);
	return (0);
}

int		db_delete(t_server *server)
{
	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->argc < 2, db_msg(server, MSG_DELETE_USAGE), 0);
	if (strcmp(server->args[1], "--database") == 0)
		return (db_deletedb(server));
	else if (strcmp(server->args[1], "--table") == 0)
		return (db_deletetbl(server));
	else if (strcmp(server->args[1], "--record") == 0)
		return (db_deletekey(server));
	else
		return (db_msg(server, MSG_DELETE_USAGE));
	return (0);
}

int		db_exit(t_server *server)
{
	CHK1(server->argc != 1, db_reply(server, "usage: EXIT\n"), 0);
	db_reply(server, "GOODBYE!");
//	fcloseall();
	db_server_clean(server);
	free(server);
	server = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}
