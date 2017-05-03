/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/05/03 15:41:11 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			db_get_print(t_server *server, FILE *fp, size_t size)
{
	char	*buf;

	buf = ft_strnew(size);
	CHK2(fgets(buf, size, fp) == NULL, free(buf), db_err(server, "FGETS ERROR"), -1);
	db_reply(server, "VALUE:\t%s\n", buf);
	free(buf);
	return (0);
}

int			db_get(t_server *server)
{
	char			*filename;
	FILE			*fp;
	int			fd;
	struct stat		st;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 2, db_reply(server, "usage: GET key\n"), 0);
	if (strncasecmp(server->args[1], "all", 3) == 0)
		return(db_getall(server));
	filename = ft_strjoinf("/", db_gethash(server, server->args[1]), STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(server->tblpath, filename, STRJOIN_FREE_SRC2);
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		(errno == ENOENT) ? db_reply(server, "Record Not Found\n") : db_err(server, "FOPEN ERROR");
		free(filename);
		return (-1);
	}
	fd = fileno(fp);
	CHK2(fstat(fd, &st) == -1, free(filename), db_err(server, "FSTAT ERROR"), -1);
	db_get_print(server, fp, st.st_size * 2);
	CHK2(fclose(fp) == EOF, free(filename), db_err(server, "FCLOSE ERROR"), -1);
	free(filename);
	return (0);
}
