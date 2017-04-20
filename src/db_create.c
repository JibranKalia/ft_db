/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 23:52:38 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

struct stat st = {0};

void			db_create(void)
{
	char		*path;
	char		str[DB_NAME_BUFF];

	printf("Enter DB name\n");
	scanf("%s", str);
	path = ft_strjoin("./Databases/", str);
	if (stat(path, &st) == -1)
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

	printf("Create a table\n");
	scanf("%s", t_name);
	temp = ft_strjoin(path, "/");
	temp = ft_strjoin(temp, t_name);
	if (stat(temp, &st) == -1)
		index = open(temp, O_CREAT);
	else
	{
		printf("Table exists with same name\n");
		table_create(path);
	}
}
void			db_load()
{
	//
}
