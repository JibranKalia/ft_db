/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:56:09 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 13:01:22 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

char	*g_db_strtable[] =
{
	"LOAD",
	"SET",
	"GET",
	"DELETE",
	"EXIT",
	"exit"
};

int		(*g_db_functable[]) (t_client *) =
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

char	*db_read_line(void)
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

void	db_split_line(t_client *client)
{
	client->argc = ft_countwords(client->line, ' ');
	client->args = ft_strsplit(client->line, ' ');
	return ;
}

int		db_execute(t_client *client)
{
	int i;

	i = 0;
	if (client->args[0] == NULL)
		return (0);
	while (i < PROTO_FUNC_NUM)
	{
		if (strncmp(client->args[0], g_db_strtable[i], strlen(g_db_strtable[i])) == 0)
			return (*g_db_functable[i])(client);
		++i;
	}
	printf("Command Not Recognized\n");
	return (0);
}

t_client *db_client_init(void)
{
	t_client	*client;

	client = (t_client *)ft_memalloc(sizeof(t_client));
	client->flag_db_load = false;
	return (client);
}

void	db_loop(t_client *client)
{
	while (1)
	{
		printf("> ");
		client->line = db_read_line();
		db_split_line(client);
		db_execute(client);
		ft_strclr(client->line);
		ft_tbldel(client->args);
	}
}

int		main(int argc, char **argv)
{
	t_client	*client;
	
//	ht_test();
	client = db_client_init();
	db_init(client);
	db_loop(client);
}
