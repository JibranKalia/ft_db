/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 20:39:36 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 22:00:29 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	db_msg(int code)
{
	if (code == 1)
		printf("Error: Database not found. Use: LOAD --database database_name\n");
	else if (code == 2)
		printf("Error: Table not found. Use: LOAD --table table_name\n");
	else if (code == 5)
		printf("usage: DELETE [--database || --table || --record] KEY\n");
	else if (code == 6)
		printf("usage: DELETE --record KEY\n");
	return (0);
}
