/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/22 17:52:17 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int		db_loaddb(t_client *client)
{
	if (client->dbpath == NULL)
		client->dbpath = strdup("./DBFILES/");
	printf("Database Path = %s\n", client->dbpath);
	if (mkdir(client->dbpath, 0777) == -1)
	{
		if (errno == EEXIST)
			client->flag_db_load = true;
		else
			perror("MKDIR ERROR");
	}
	else
		client->flag_db_load = true;
	return (0);
}

int				db_load(t_client *client)
{
	char		*tmp;
	struct stat	st = {0};

	CHK1(client->argc != 3, printf("usage: LOAD [--database || --table] name\n"), 0);
	if (strcmp(client->args[1], "--database") == 0)
	{
		ft_strclr(client->dbpath);
		tmp = client->args[2];
		tmp = ft_strjoin("./", tmp);
		client->dbpath = ft_strjoinf(tmp, "/", STRJOIN_FREE_SRC1);
		return (db_loaddb(client));
	}
	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	if (strcmp(client->args[1], "--table"))
		return (printf("usage: LOAD [--database || --table] name\n"));
	tmp = client->args[2];
	tmp = ft_strjoin(tmp, "/");
	client->tblpath = ft_strjoinf(client->dbpath, tmp, STRJOIN_FREE_SRC2);
	printf("Table Path = %s\n", client->tblpath);
	if (mkdir(client->tblpath, 0777) == -1)
	{
		if (errno == EEXIST)
			client->flag_tbl_load = true;
		else
			perror("MKDIR ERROR");
	}
	client->logpath = ft_strjoin(client->tblpath, "log");
	if (stat(client->logpath, &st) == -1)
		if (open(client->logpath, O_CREAT) == -1)
			perror("OPEN ERROR");
	return (0);
}
