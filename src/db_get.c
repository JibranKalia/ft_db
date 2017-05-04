/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/05/03 22:51:07 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

char	*db_printer(char *value)
{
	int 	j; 
	int	i;
	int	len;
	char	*buf;

	j = 0;
	len = strlen(value) * 2;
	buf = ft_strnew(len);
	if (*value == '\n')
		++value;
	memcpy(buf, "KEY: ", 5);
	j = 5;
	i = 0;
	while (*value)
	{
		if (*value == '\n')
		{
			memcpy(&buf[j], "\nKEY: ", 6);
			++value;
			j += 6;
			i = 0;
		}
		else if (*value == ':')
		{
			if (i < 3)
			{
				memcpy(&buf[j], "\t", 1);
				++j;
			}
			memcpy(&buf[j], "\t\t| VALUE: ", 11);
			++value;
			j += 11;
		}
		else if (*value == ',')
		{
			memcpy(&buf[j], "\t\t", 2);
			j += 2;
			++value;
		}
		else
		{
			buf[j] = *value;
			++j;
			++value;
			++i;
		}
	}
	buf[j] = 0;
	return (buf);
}

int			db_get_print(t_server *server, FILE *fp, size_t size)
{
	char	*buf;
	char	*parsed;

	buf = ft_strnew(size);
	CHK2(fgets(buf, size, fp) == NULL, free(buf), db_err(server, "FGETS ERROR"), -1);
	parsed = db_printer(buf);
	REPLY(parsed);
	free(buf);
	free(parsed);
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
	CHK1(server->argc != 2, REPLY("usage: GET key"), 0);
	if (strncasecmp(server->args[1], "all", 3) == 0)
		return(db_getall(server));
	filename = ft_strjoinf("/", db_gethash(server, server->args[1]), STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(server->tblpath, filename, STRJOIN_FREE_SRC2);
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		(errno == ENOENT) ? REPLY("Record Not Found") : db_err(server, "FOPEN ERROR");
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
