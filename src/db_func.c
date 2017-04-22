/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/21 21:40:10 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		db_set(char **args)
{
	printf("DB_SET\n");
	return (1);
}
int		db_get(char **args)
{
	printf("DB_GET\n");
	return (1);
}
int		db_delete(char **args)
{
	printf("DB_DELETE\n");
	return (1);
}
int		db_exit(char **args)
{
	printf("DB_EXIT\n");
	ft_tbldel(args);
	exit(EXIT_SUCCESS);
	return (0);
}
