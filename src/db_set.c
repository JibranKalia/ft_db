/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/26 20:12:54 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			db_set(t_server *server)
{
	char		*hash;
	char		*filename;
	FILE		*fp;

	CHK1(server->flag_db_load == false, db_msg(server, MSG_DB_MISSING), 0);
	CHK1(server->flag_tbl_load == false, db_msg(server, MSG_TBL_MISSING), 0);
	CHK1(server->argc != 3, db_reply(server, "usage: SET key value\n"), 0);
	hash = db_gethash(server, cleanstr(server->args[1]));
	filename = ft_strjoinf("/", hash, STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(server->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2((fp = fopen(filename, "w+")) == NULL, free(filename), perror("FOPEN ERROR: "), -1);
	CHK2(fputs(cleanstr(server->args[2]), fp) == EOF, free(filename), perror("FPUTS ERROR"), -1);
	CHK2((fclose(fp) == EOF), free(filename), perror("FCLOSE ERROR"), -1);
	db_reply(server, "Record Saved\n");
	free(filename);
	return (0);
}
