/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 20:39:36 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/27 18:50:18 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	db_msg(t_server *server, int code)
{
	if (code == MSG_WELCOME)
	{
		db_reply(server, "*********************************************\n"
				"Welcome to FT_DB!\n"
				"Type HELP to get started\n"
				"Have Fun and make sure to enjoy responsibly.\n"
				"*********************************************\n");
	}
	else if (code == MSG_HELP)
	{
		db_reply(server,  "**********************************************************\n"
				"Step 1: Choose Database. Use: LOAD --database database_name\n"
				"Step 2: Choose Table. Use: LOAD --table table_name\n"
				"Step 3: Save Record. Use: SET Key Value\n"
				"Step 4: Retrieve Record: Use: GET Key\n"
				"Step 5: Delete Record. Use: DELETE --record KEY\n"
				"Step 6: Exit. Use: EXIT\n"
				"**********************************************************\n");
	}
	else if (code == MSG_DB_MISSING)
		db_reply(server, "Error: Database not found. Use: LOAD --database database_name\n");
	else if (code == MSG_TBL_MISSING)
		db_reply(server, "Error: Table not found. Use: LOAD --table table_name\n");
	else if (code == MSG_DELETE_USAGE)
		db_reply(server, "usage: DELETE [--database || --table || --record] KEY\n");
	else if (code == MSG_DELETE_USAGE2)
		db_reply(server, "usage: DELETE --record KEY\n");
	return (0);
}

int		db_reply(t_server *server, const char *fmt, ...)
{
	va_list		ap;
	va_list		clone1;
	va_list		clone2;
	int			i;

	va_start(ap, fmt);
	va_copy(clone1, ap);
	va_copy(clone2, ap);
	if (server->fd != STDOUT_FILENO)
		i = vdprintf(server->fd, fmt, clone1);
	i = vprintf(fmt, clone2);
	return (i);
}
