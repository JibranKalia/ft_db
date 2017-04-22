/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:24:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/21 22:39:07 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		db_set(t_client *client)
{
	printf("DB_SET Num of Args: %d\n", client->argc);
	return (1);
}
int		db_get(t_client *client)
{
	printf("DB_GET Num of Args: %d\n", client->argc);
	return (1);
}
int		db_delete(t_client *client)
{
	printf("DB_DELETE Num of Args: %d\n", client->argc);
	printf("DB_DELETE\n");
	return (1);
}
int		db_exit(t_client *client)
{
	printf("DB_EXIT Num of Args: %d\n", client->argc);
	ft_strclr(client->line);
	ft_tbldel(client->args);
	free(client);
	exit(EXIT_SUCCESS);
	return (0);
}
