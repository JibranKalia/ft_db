/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:53:25 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/19 17:33:44 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void			create_db()
{
	struct stat st = {0};
	char		*name;
	char		str[BUFF_SIZE];

	printf("Enter DB name\n");
	scanf("%s", str);
	name = ft_strjoin("./", str);
	if (stat(name, &st) == -1)
		mkdir(str, 0777);
	else
		printf("DB already exists with same name\n");
}

