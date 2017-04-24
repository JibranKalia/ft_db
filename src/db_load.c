/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/23 20:29:02 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	db_loaddb(t_client *client)
{
	if (client->dbpath == NULL)
		client->dbpath = strdup("./DBFILES");
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

static int	db_loadtbl(t_client *client)
{
	struct stat	st = {0};

	printf("Table Path = %s\n", client->tblpath);
	if (mkdir(client->tblpath, 0777) == -1)
	{
		if (errno == EEXIST)
			client->flag_tbl_load = true;
		else
			perror("MKDIR ERROR");
	}
	else
		client->flag_tbl_load = true;
	client->logpath = ft_strjoin(client->tblpath, "/");
	client->logpath = ft_strjoinf(client->logpath, "log", STRJOIN_FREE_SRC1);
	printf("Log Path = %s\n", client->logpath);
	if (stat(client->logpath, &st) == -1)
		if (open(client->logpath, O_CREAT) == -1)
			perror("OPEN ERROR");
	return (0);

}

int		db_load(t_client *client)
{
	char		*tmp;

	CHK1(client->argc != 3, printf("usage: LOAD [--database || --table] name\n"), 0);
	tmp = client->args[2];
	if (strcmp(client->args[1], "--database") == 0)
	{
		ft_strclr(client->dbpath);
		client->dbpath = ft_strjoin("./", tmp);
		return (db_loaddb(client));
	}
	else if (strcmp(client->args[1], "--table") == 0)
	{
		CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
		ft_strclr(client->tblpath);
		client->tblpath = ft_strjoin(client->dbpath, "/");
		client->tblpath = ft_strjoinf(client->tblpath, tmp, STRJOIN_FREE_SRC1);
		return (db_loadtbl(client));
	}
	else
		return (printf("usage: LOAD [--database || --table] name\n"));
}
