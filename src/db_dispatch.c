/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:19:31 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 21:17:25 by jkalia           ###   ########.fr       */
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
	"exit"
};

static int		(*g_db_functable[]) (t_client *) =
{
	&db_load,
	&db_set,
	&db_get,
	&db_delete,
	&db_exit,
	&db_exit
};

/*
** Deletes Trailing Whitespace
*/

static char		*db_read_line(void)
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

static void		db_split_line(t_client *client)
{
	client->argc = ft_countwords(client->line, ' ');
	client->args = ft_strsplit(client->line, ' ');
	return ;
}

static int		db_dispatch(t_client *client)
{
	int		i;
	char	*in;

	i = 0;
	if (client->args[0] == NULL)
		return (0);
	in = client->args[0];
	while (i < PROTO_FUNC_NUM)
	{
		if (strncasecmp(in, g_db_strtable[i], strlen(in)) == 0)
			return (*g_db_functable[i])(client);
		++i;
	}
	printf("Command Not Recognized\n");
	return (0);
}

void			db_loop(t_client *client)
{
	while (1)
	{
		printf("> ");
		client->line = db_read_line();
		db_split_line(client);
		db_dispatch(client);
		ft_tbldel(client->args);
		ft_strclr(client->line);
	}
}
