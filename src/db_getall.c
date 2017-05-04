/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 21:34:47 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

char			*db_catvalue(t_server *server)
{
	char			*buf;
	int				len = 0;
	int				i;
	int				j;
	int				k;
	t_db_file		**tmp;

	i = 0;
	tmp = (t_db_file **)server->files->contents;
	while (i < server->files->end)
	{
		len += tmp[i]->statinfo.st_size + 2;
		++i;
	}
	buf = ft_strnew(len);
	i = 0;
	j = 0;
	while (i < server->files->end)
	{
		k = strlen(tmp[i]->value);
		memcpy(&buf[j], tmp[i]->value, k);
		j += k;
		memcpy(&buf[j], "\n", 1);
		++i;
		++j;
	}
	buf[j - 1] = 0; //Removing the last newline.
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
	return (0);
}

int			db_getall(t_server *server)
{
	CHK(db_getfiles(server) == -1, -1);
	CHK(db_getall_print(server) == -1, -1);
	return (0);
}
