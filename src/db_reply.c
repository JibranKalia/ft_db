/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_reply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 20:39:36 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/04 16:13:26 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	db_msg(t_server *server, int code)
{
	if (code == MSG_WELCOME)
	{
		REPLY("*********************************************\n"
				"Welcome to FT_DB!\n"
				"Type HELP to get started\n"
				"Have Fun and make sure to enjoy responsibly.\n"
				"*********************************************");
	}
	else if (code == MSG_HELP)
	{
		REPLY( "**********************************************************\n"
				"Step 1: Choose Database. Use: LOAD --database database_name\n"
				"Step 2: Choose Table. Use: LOAD --table table_name\n"
				"Step 3: Save Record. Use: CREATE Key Value\n"
				"Step 4: Retrieve Record: Use: GET Key\n"
				"Step 5: Update Record: Use: UPDATE Key Value\n"
				"Step 6: Retrieve Updated Record: Use: GET Key\n"
				"Step 7: Delete Record. Use: DELETE --record KEY\n"
				"Step 8: Check if deleted correctly: Use: GET Key\n"
				"Step 9: Exit. Use: EXIT\n"
				"**********************************************************");
	}
	else if (code == MSG_DB_MISSING)
		REPLY("Error: Database not found. Use: LOAD --database database_name");
	else if (code == MSG_TBL_MISSING)
		REPLY("Error: Table not found. Use: LOAD --table table_name");
	else if (code == MSG_DELETE_USAGE)
		REPLY("usage: DELETE [--database || --table || --record] KEY");
	else if (code == MSG_DELETE_USAGE2)
		REPLY("usage: DELETE --record KEY");
	return (0);
}

int		db_err(t_server *server, const char *str)
{
	char	*buf;
	char	err[256];

	strerror_r(errno, err, 255);
	asprintf(&buf, "%s: %s", str, err);
	REPLY("%s", buf);
	free(buf);
	return (-1);
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
	{
		i = vdprintf(server->fd, fmt, clone1);
	}
	i = vdprintf(STDOUT_FILENO, fmt, clone2);
	dprintf(STDOUT_FILENO, "\n");
	va_end(clone1);
	va_end(clone2);
	va_end(ap);
	return (i);
}
