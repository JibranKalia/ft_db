/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 13:18:10 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int		db_stringcheck(char *s)
{
	while (*s)
	{
		if (*s == ':')
			return (*s);
		++s;
	}
	return (0);
}

static int		db_writefile(char *filename, char *key, t_server *server)
{
	FILE	*fp;
	int		illegal;

	illegal = db_stringcheck(server->args[2]);
	CHK1(illegal != 0, REPLY("Illegal Character: %c", illegal), -1);
	fp = fopen(filename, "w+");
	CHK2(fp == NULL, free(filename), ERR("FOPEN ERROR: "), -1);
	CHK1(fputs(key, fp) == EOF, ERR("FPUTS ERROR"), -1);
	CHK1(fputs(":", fp) == EOF, ERR("FPUTS ERROR"), -1);
	CHK1(fputs(server->args[2], fp) == EOF, ERR("FPUTS ERROR"), -1);
	CHK1(fclose(fp) == EOF, ERR("FCLOSE ERROR"), -1);
	return (0);
}

int				db_set(t_server *server)
{
	char	*hash;
	char	*filename;
	int		illegal;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, REPLY("usage: SET key value"), 0);
	illegal = db_stringcheck(server->args[1]);
	CHK1(illegal != 0, REPLY("Illegal Character: %c", illegal), -1);
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
	CHK2(db_writefile(filename, server->args[1], server) == -1,
			free(hash), free(filename), -1);
	free(hash);
	free(filename);
	REPLY("Record Saved");
	return (0);
}

int				db_update(t_server *server)
{
	char		*hash;
	char		*filename;
	int			chk;

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
