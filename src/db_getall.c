/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 18:44:31 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			db_getall_print(t_server *server)
{
	char			*buf;
	int				len = 0;
	int				i = 0, j = 0, k = 0;
	t_db_file		**tmp;
	
	CHK1(server->files == NULL, ERR("File Array not present"), -1);
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		len += tmp[i]->statinfo.st_size + 10;
		++i;
	}
	buf = ft_strnew(len);
	i = 0;
	while (i < server->files->end)
	{
		k = strlen(tmp[i]->value);
		memcpy(&buf[j], "VALUE: ", 7);
		j += 7;
		memcpy(&buf[j], tmp[i]->value, k);
		j += k;
		memcpy(&buf[j], "\n", 1);
		++j;
		++i;
	}
	db_reply(server, buf);
	free(buf);
	return (0);
}

int			db_getall(t_server *server)
{
	int chk;

	CHK(db_arrinit(server) == -1, -1);
	chk = db_ls(server);
	CHK1(((server->files->end == 0) || chk == -1), REPLY("DB LS Failed\n"), -1);
	CHK(db_readvalue(server) == -1, -1);
	CHK(db_getall_print(server) == -1, -1);
	return (0);
}
