/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/22 13:50:24 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void			db_create(void)
{
	char		*path;
	char		str[DB_NAME_BUFF];
	struct stat	*st;

	printf("Enter DB name\n");
	scanf("%s", str);
	path = ft_strjoin("./Databases/", str);
	if (stat(path, st) == -1)
		mkdir(path, 0777);
	else
	{
		printf("DB already exists with same name\n");
		db_create();
	}
	table_create(path);
}

void			table_create(char *path)
{
	char		*t_name;
	int			index;
	char		*temp;
	struct stat	*st;

	printf("Create a table\n");
	scanf("%s", t_name);
	temp = ft_strjoin(path, "/");
	temp = ft_strjoin(temp, t_name);
	if (stat(temp, st) == -1)
		index = open(temp, O_CREAT);
	else
	{
		printf("Table exists with same name\n");
		table_create(path);
	}
}

void			db_init(t_client *client)
{
	char		*path;

	path = "./DBFILES/";
	client->dbpath = strdup(path);
	if (mkdir(path, 0777) == -1)
		if (errno != EEXIST)
			perror("MKDIR ERROR");
}

int				db_load(t_client *client)
{
	char	*tmp;
	CHK1(client->argc != 2, printf("usage: LOAD db_name\n"), 0);
	
	tmp = client->args[1];
	tmp = ft_strjoin(tmp, "/");
	client->dbpath = ft_strjoinf(client->dbpath, tmp, STRJOIN_FREE_BOTH);
	printf("PATH = %s\n", client->dbpath);
	if (mkdir(client->dbpath, 0777) == -1)
		if (errno != EEXIST)
			perror("MKDIR ERROR");
	return (0);
}
