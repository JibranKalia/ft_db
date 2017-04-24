/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 20:39:36 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 23:18:40 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	db_msg(int code)
{
	if (code == MSG_WELCOME)
	{
		printf("*********************************************\n"
				"Welcome to FT_DB!\n"
				"Type HELP to get started\n"
				"Have Fun and make sure to enjoy responsibly.\n"
				"*********************************************\n");
	}
	else if (code == MSG_HELP)
	{
		printf( "**********************************************************\n"
				"Step 1: Choose Database. Use: LOAD --database database_name\n"
				"Step 2: Choose Table. Use: LOAD --table table_name\n"
				"Step 3: Save Record. Use: SET Key Value\n"
				"Step 4: Retrieve Record: Use: GET Key\n"
				"Step 5: Delete Record. Use: DELETE --record KEY\n"
				"Step 6: Exit. Use: EXIT\n"
				"**********************************************************\n");
	}
	else if (code == MSG_DB_MISSING)
		printf("Error: Database not found. Use: LOAD --database database_name\n");
	else if (code == MSG_TBL_MISSING)
		printf("Error: Table not found. Use: LOAD --table table_name\n");
	else if (code == MSG_DELETE_USAGE)
		printf("usage: DELETE [--database || --table || --record] KEY\n");
	else if (code == MSG_DELETE_USAGE2)
		printf("usage: DELETE --record KEY\n");
	return (0);
}
