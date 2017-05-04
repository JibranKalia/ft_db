/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:19:31 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 22:47:54 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>
# define FUNC_NUM 10

int8_t			g_commandcode = 0;

static char		*g_db_strtable[FUNC_NUM] =
{
	"LOAD",
	"SET",
	"CREATE",
	"UPDATE",
	"GET",
	"GETVAL", 
	"DELETE",
	"EXIT",
	"HELP",
	"CLEAR"
};

static int		(*g_db_functable[]) (t_server *) =
{
	&db_load,
	&db_set,
	&db_set,
	&db_update,
	&db_get,
	&db_getval,
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

char				*db_strtrim(char *src)
{
	char		*to_free;
	char		*dst;
	size_t		i;
	size_t		len;

	to_free = src;
	i = -1;
	while (*src && !isgraph(*src))
		++src;
	len = strlen(src);
	while (!isgraph(src[len - 1]) && len > 0)
		--len;
	CHK((dst = (char*)ft_memalloc(sizeof(char) * (len + 1))) == 0, NULL);
	while (++i < len)
		dst[i] = src[i];
	dst[i] = 0;
	free(to_free);
	return (dst);
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
	char	**tmp;
	int	i;

	i = 0;
	server->argc = ft_countwords(server->line, ' ');
	tmp = ft_strsplit(server->line, ' ');
	while (i < server->argc)
	{
		tmp[i] = db_strtrim(tmp[i]);
		++i;
	}
	server->args = tmp;
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
	while (i < FUNC_NUM)
	{
		if (strncasecmp(in, g_db_strtable[i], strlen(in)) == 0)
		{
			g_commandcode = i;
			return (*g_db_functable[i])(server);
		}
		++i;
	}
	REPLY("Command Not Recognized");
	return (0);
}
