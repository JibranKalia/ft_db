/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 18:11:16 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void			db_create(void)
{
	struct stat st = {0};
	char		*name;
	char		str[DB_NAME_BUFF];

	printf("Enter DB name\n");
	scanf("%s", str);
	name = ft_strjoin("./", str);
	if (stat(name, &st) == -1)
		mkdir(str, 0777);
	else
	{
		printf("DB already exists with same name\n");
		create_db();
	}
}

