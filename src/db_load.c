/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/05/05 13:26:06 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	db_loaddb(t_server *server)
{
	if (server->dbpath == NULL)
		server->dbpath = strdup("./db");
	REPLY("Database Path = %s", server->dbpath);
	if (mkdir(server->dbpath, 0777) == -1)
	{
		if (errno == EEXIST)
			server->flag_db_load = true;
		else
			db_err(server, "MKDIR ERROR");
	}
	else
		server->flag_db_load = true;
	return (0);
}

static int	db_loadtbl(t_server *server)
{
	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	if (server->tblpath == NULL)
		server->tblpath = strdup("./db/tbl");
	REPLY("Table Path = %s", server->tblpath);
	if (mkdir(server->tblpath, 0777) == -1)
	{
		if (errno == EEXIST)
			server->flag_tbl_load = true;
		else
			db_err(server, "MKDIR ERROR");
	}
	else
		server->flag_tbl_load = true;
	server->logpath = ft_strjoin(server->tblpath, "/");
	server->logpath = ft_strjoinf(server->logpath, "log", STRJOIN_FREE_SRC1);
	return (0);
}

int			db_load(t_server *server)
{
	char		*tmp;

	CHK1(server->argc < 3,
			REPLY("usage: LOAD [--database || --table] name"), 0);
	tmp = server->args[2];
	if (strcmp(server->args[1], "--database") == 0)
	{
		ft_strclr(server->dbpath);
		server->dbpath = ft_strjoin("./", tmp);
		return (db_loaddb(server));
	}
	else if (strcmp(server->args[1], "--table") == 0)
	{
		CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
		ft_strclr(server->tblpath);
		server->tblpath = ft_strjoin(server->dbpath, "/");
		server->tblpath = ft_strjoinf(server->tblpath, tmp, STRJOIN_FREE_SRC1);
		return (db_loadtbl(server));
	}
	else
		return (REPLY("usage: LOAD [--database || --table] name"));
}
