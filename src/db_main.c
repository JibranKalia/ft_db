/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:56:09 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/21 21:39:40 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

#define PROTO_FUNC_NUM (4)

char	*g_db_strtable[] =
{
	"SET",
	"GET",
	"DELETE",
	"EXIT"
};

int		(*g_db_functable[]) (char **) =
{
	&db_set,
	&db_get,
	&db_delete,
	&db_exit
};

char	*db_read_line(void)
{
	char		*line;
	size_t		bufsize;

	bufsize = 0;
	line = NULL;
	getline(&line, &bufsize, stdin);
	return (line);
}

char	**db_split_line(char *line)
{
	char	**args;

	args = ft_strsplit(line, ' ');
	return (args);
}

int		db_execute(char **args)
{
	int i;

	i = 0;
	if (args[0] == NULL)
		return (-1);
	while (i < PROTO_FUNC_NUM)
	{
		if (strncmp(args[0], g_db_strtable[i], strlen(g_db_strtable[i])) == 0)
			return (*g_db_functable[i])(args);
		++i;
	}
	printf("Command Not Recognized\n");
	return (-1);
}

void	db_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	while (1)
	{
		printf("> ");
		line = db_read_line();
		args = db_split_line(line);
		free(line);
		status = db_execute(args);
		ft_tbldel(args);
	}
}

int		main(int argc, char **argv)
{
	db_loop();
}
