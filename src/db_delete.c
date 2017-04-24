/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 22:15:40 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	db_deletetbl(t_client *client)
{
	char	*buf;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	buf = ft_strjoin("rm -rf ", client->tblpath);
	printf("Removing: %s\n", client->tblpath);
	system(buf);
	client->flag_tbl_load = false;
	free(buf);
	return (0);
}

static int	db_deletedb(t_client *client)
{
	char	*buf;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	buf = ft_strjoin("rm -rf ", client->dbpath);
	printf("Removing: %s\n", client->dbpath);
	system(buf);
	client->flag_db_load = false;
	free(buf);
	return (0);
}

int		db_deletekey(t_client *client)
{
	char	*filename;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 3, db_msg(MSG_DELETE_USAGE2), 0);
	filename = ft_strjoinf("/", db_gethash(client, client->args[2]), STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(client->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2(remove(filename) == -1, free(filename), perror("REMOVE ERROR"), -1);
	printf("Removing: %s\n", filename);
	free(filename);
	return (0);
}

int		db_delete(t_client *client)
{
	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->argc < 2, db_msg(MSG_DELETE_USAGE), 0);
	if (strcmp(client->args[1], "--database") == 0)
		return (db_deletedb(client));
	else if (strcmp(client->args[1], "--table") == 0)
		return (db_deletetbl(client));
	else if (strcmp(client->args[1], "--record") == 0)
		return (db_deletekey(client));
	else
		return (db_msg(MSG_DELETE_USAGE));
	return (0);
}

int		db_exit(t_client *client)
{
	CHK1(client->argc != 1, printf("usage: EXIT\n"), 0);
	printf("GOODBYE!");
//	fcloseall();
	db_client_clean(client);
	free(client);
	client = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}
