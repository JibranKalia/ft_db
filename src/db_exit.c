/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 21:59:33 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

void	db_msg(int code)
{
	if (code == 1)
		printf("Error: Database not found. Use: LOAD --database database_name\n");
	else if (code == 2)
		printf("Error: Table not found. Use: LOAD --table table_name\n");
}

int		db_deletetbl(t_client *client)
{
	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	return (0);
}

int		db_deletedb(t_client *client)
{
	char	*buf;

	buf = ft_strjoin("rm -rf ", client->dbpath);
	printf("Delete Database: %s\n", buf);
	system(buf);
	return (0);
}

int		db_delete(t_client *client)
{
	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->argc < 2, printf("usage: DELETE [--database || --table || --record]\n"), 0);
	if (strcmp(client->args[1], "--database") == 0)
		return (db_deletedb(client));
	return (1);
}

int		db_exit(t_client *client)
{
	CHK1(client->argc != 1, printf("usage: EXIT\n"), 0);
	printf("GOODBYE!");
	db_client_clean(client);
	free(client);
	client = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}
