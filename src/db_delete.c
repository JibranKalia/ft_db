/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 21:50:59 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_deletetbl(t_server *server)
{
	char	*filename;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	filename = server->tblpath;
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK2(remove(filename) == -1, free(filename),
			db_err(server, "REMOVE ERROR"), -1);
	REPLY("Table Removed");
	server->flag_tbl_load = false;
	return (0);
}

static int	db_deletedb(t_server *server)
{
	char	*filename;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	filename = server->dbpath;
	CHK2(remove(filename) == -1, free(filename),
			db_err(server, "REMOVE ERROR"), -1);
	REPLY("Database Removed");
	server->flag_db_load = false;
	return (0);
}

static int	db_deletekey(t_server *server)
{
	char	*filename;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, db_msg(server, MSG_DELETE_USAGE2), 0);
	asprintf(&filename, "%s/%s", server->tblpath,
			db_gethash(server, server->args[2]));
	CHK2(remove(filename) == -1, free(filename),
			db_err(server, "REMOVE ERROR"), -1);
	REPLY("Removing: %s", filename);
	free(filename);
	return (0);
}

int			db_delete(t_server *server)
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

int			db_exit(t_server *server)
{
	CHK1(server->argc != 1, REPLY("usage: EXIT"), 0);
	REPLY("GOODBYE!");
	db_server_clean(server);
	server = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}
