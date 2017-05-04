/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 21:05:27 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int		db_stringcheck(char *s)
{
	while (*s)
	{
		if (*s == '(' || *s == ')' || *s == '{'
				|| *s == '}' || *s == '[' || *s == ']')
			return (*s);
		++s;
	}
	return (0);
}
static int		db_writefile(char *filename, char *key, t_server *server)
{
	char		*tmp1;
	char		*tmp2;
	FILE		*fp;
	int		illegal;

	illegal = db_stringcheck(server->args[2]);
	CHK1(illegal != 0, REPLY("Illegal Character: %c", illegal), -1);
	fp = fopen(filename, "w+");
	CHK2(fp == NULL, free(filename), ERR("FOPEN ERROR: "), -1);
	asprintf(&tmp1, "{%s}", key);
	CHK2(fputs(tmp1, fp) == EOF, free(tmp1), ERR("FPUTS ERROR"), -1);
	asprintf(&tmp2, "[%s]", server->args[2]);
	CHK3(fputs(tmp2, fp) == EOF, free(tmp1), free(tmp2), ERR("FPUTS ERROR"), -1);
	CHK3(fclose(fp) == EOF, free(tmp1), free(tmp2), ERR("FCLOSE ERROR"), -1);
	free(tmp1);
	free(tmp2);
	return (0);
}

int			db_set(t_server *server)
{
	char		*hash;
	char		*filename;
	int		chk;
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
	chk = db_writefile(filename, server->args[1], server);
	free(hash);
	free(filename);
	if (chk != -1)
	{
		REPLY("Record Saved");
		server->flag_value = false;
	}
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
	{
		REPLY("Record Updated");
		server->flag_value = false;
	}
	return ((chk == 0) ? 0 : -1);
}
