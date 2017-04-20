/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 18:08:54 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void			db_create(void)
{
	struct stat st = {0};
	char		*name;
	char		str[DB_NAME_BUFF];
	bool		file_exists;


	file_exists = false;

	do
	{
		printf("Enter DB name. (Limit 50 Characters)\n");
		scanf("%s", str);
		name = ft_strjoin("./", str);
		if (stat(name, &st) == -1)
		{
			mkdir(str, 0777);
			file_exists = true;
		}
	}
	while (file_exists == false);
}

