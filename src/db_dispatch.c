/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:19:31 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/26 17:23:27 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static char		*g_db_strtable[] =
{
	"LOAD",
	"SET",
	"GET",
	"DELETE",
	"EXIT",
	"HELP",
	"CLEAR"
};

static int		(*g_db_functable[]) (t_server *) =
{
	&db_load,
	&db_set,
	&db_get,
	&db_delete,
	&db_exit,
	&db_help,
	&db_clear
};

/*
** Deletes Trailing Whitespace
*/

int				db_help(t_server *server)
{
	db_msg(server, MSG_HELP);
	return (0);
}

int				db_clear(t_server *server)
{
	if (strncasecmp(server->args[0], "clear", 5) == 0)
		system(server->args[0]);
	return (0);
}

char			*db_read_line(void)
{
	char		*line;
	size_t		bufsize;
	int			i;

	bufsize = 0;
	line = NULL;
	getline(&line, &bufsize, stdin);
	i = strlen(line) - 1;
	line[i] = 0;
	while (i > 0 && isspace(line[i]))
	{
		line[i] = 0;
		--i;
	}
	return (line);
}

void			db_split_line(t_server *server)
{
	server->argc = ft_countwords(server->line, ' ');
	server->args = ft_strsplit(server->line, ' ');
	return ;
}

int				db_dispatch(t_server *server)
{
	int		i;
	char	*in;

	i = 0;
	if (server->args[0] == NULL)
		return (0);
	in = server->args[0];
	while (i < PROTO_FUNC_NUM)
	{
		if (strncasecmp(in, g_db_strtable[i], strlen(in)) == 0)
			return (*g_db_functable[i])(server);
		++i;
	}
	db_reply(server, "Command Not Recognized\n");
	return (0);
}
