/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/23 22:02:19 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		db_set(t_client *client)
{
	char		*hash;
	char		*filename;
	FILE		*fp;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 3, printf("usage: SET key value\n"), 0);
	hash = db_gethash(client, client->args[1]);
	printf("Hash = %s\n", hash);
	filename = ft_strjoinf("/", hash, STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(client->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2((fp = fopen(filename, "w+")) == NULL, free(filename), perror("FOPEN ERROR: "), -1);
	CHK2(fputs(client->args[2], fp) == EOF, free(filename), perror("FPUTS ERROR"), -1);
	CHK2((fclose(fp) == EOF), free(filename), perror("FCLOSE ERROR"), -1);
	free(filename);
	return (0);
}

/**
 * Use Hash to create file
 * Write Value onto file
 * Close file
 * add hash to log file. (log file not yet)
**/

int		db_get_print(FILE *fp, size_t size, t_client *client)
{
	char	*buf;

	buf = (char *)malloc(size);
	bzero(buf, size);
	CHK2(fgets(buf, size, fp) == NULL, free(buf), perror("FGETS ERROR"), -1);
	printf("Record Value: %s\n", buf);
	free(buf);
	return (0);
}

int		db_get(t_client *client)
{
	char		*filename;
	FILE		*fp;
	int		fd;
	struct stat	st;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 2, printf("usage: GET key\n"), 0);
	filename = ft_strjoinf("/", db_gethash(client, client->args[1]), STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(client->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2(((fp = fopen(filename, "r")) == NULL), free(filename), perror("FOPEN ERROR"), -1);
	fd = fileno(fp);
	CHK2(fstat(fd, &st) == -1, free(filename), perror("FSTAT ERROR"), -1);
	db_get_print(fp, st.st_size * 2, client);
	CHK2(fclose(fp) == EOF, free(filename), perror("FCLOSE ERROR"), -1);
	free(filename);
	return (0);
}

/*
 * Ignore LOG file.
 * man opendir()
 * Find the file.
 * Open file / Read. Put it to output.
 * Close file.
**/
