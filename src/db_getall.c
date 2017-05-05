/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 13:01:19 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	valuecount(t_server *server)
{
	t_db_file		**tmp;
	int				len;
	int				i;

	i = 0;
	len = 0;
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		len += tmp[i]->statinfo.st_size + 2;
		++i;
	}
	return (len);
}

char		*db_catvalue(t_server *server)
{
	char			*buf;
	int				i;
	int				j;
	int				k;
	t_db_file		**tmp;

	buf = ft_strnew(valuecount(server));
	i = 0;
	j = 0;
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		k = strlen(tmp[i]->value);
		memcpy(&buf[j], tmp[i]->value, k);
		j += k;
		memcpy(&buf[j], "\n", 1);
		++i;
		++j;
	}
	buf[j - 1] = 0;
	return (buf);
}

int			db_getall_print(t_server *server)
{
	char	*tmp;
	char	*parsed;

	CHK1(server->files == NULL, ERR("File Array not present"), -1);
	tmp = db_catvalue(server);
	parsed = db_printer(tmp);
	REPLY(parsed);
	free(tmp);
	free(parsed);
	return (0);
}

int			db_getall(t_server *server)
{
	CHK(db_getfiles(server) == -1, -1);
	CHK(db_getall_print(server) == -1, -1);
	return (0);
}
