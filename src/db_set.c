/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 19:36:00 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int		db_writefile(char *filename, char *key, t_server *server)
{
	char		*tmp;
	char		*tmp2;
	FILE		*fp;
	char		**values;

	fp = fopen(filename, "w+");
	CHK2(fp == NULL, free(filename), ERR("FOPEN ERROR: "), -1);
	asprintf(&tmp, "KEY: {%15s} | VALUE: ", key);
	CHK2(fputs(tmp, fp) == EOF, free(filename), ERR("FPUTS ERROR"), -1);
	values = ft_strsplit(server->args[2], ',');
	CHK2(fputs("[", fp) == EOF, free(filename), ERR("FPUTS ERROR"), -1);
	while (*values)
	{
		asprintf(&tmp2, "%15s", *values);
		CHK2(fputs(tmp2, fp) == EOF, free(filename), ERR("FPUTS ERROR"), -1);
		values++;
	}
	CHK2(fputs("]", fp) == EOF, free(filename), ERR("FPUTS ERROR"), -1);
	CHK2(fclose(fp) == EOF, free(filename), ERR("FCLOSE ERROR"), -1);
	ft_tbldel(values);
	return (0);
}

int			db_set(t_server *server)
{
	char		*hash;
	char		*filename;
	int		chk;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, REPLY("usage: SET key value"), 0);
	hash = db_gethash(server, server->args[1]);
	asprintf(&filename, "%s/%s", server->tblpath, hash);
	if (access(filename, F_OK) != -1)
	{
		CHK(REPLY("Record exists. Use UPDATE"), 0);
	}
	else if (errno != ENOENT)
	{
		CHK(ERR("ACCESS ERROR: "), -1);
	}
	chk = db_writefile(filename, server->args[1], server);
	free(hash);
	free(filename);
	if (chk != -1)
		REPLY("Record Saved");
	return ((chk == 0) ? 0 : -1);
}

int			db_update(t_server *server)
{
	char		*hash;
	char		*filename;
	int		chk;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, REPLY("usage: UPDATE key value"), 0);
	hash = db_gethash(server, server->args[1]);
	asprintf(&filename, "%s/%s", server->tblpath, hash);
	chk = db_writefile(filename, server->args[1], server);
	free(hash);
	free(filename);
	if (chk != -1)
		REPLY("Record Updated");
	return ((chk == 0) ? 0 : -1);
}
