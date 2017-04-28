/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:51:30 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/28 11:38:37 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			db_set(t_client *client)
{
	char		*hash;
	char		*filename;
	FILE		*fp;
	char		**values;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 3, printf("usage: SET key value\n"), 0);
	hash = db_gethash(client, client->args[1]);
	filename = ft_strjoinf("/", hash, STRJOIN_FREE_SRC2);
	filename = ft_strjoinf(client->tblpath, filename, STRJOIN_FREE_SRC2);
	CHK2((fp = fopen(filename, "w+")) == NULL, free(filename), perror("FOPEN ERROR: "), -1);
	values = db_values(client->args[2]);
	while (*values)
	{
		CHK2(fputs(*values, fp) == EOF, free(filename), perror("FPUTS ERROR"), -1);
		CHK2(fputs("\t", fp) == EOF, free(filename), perror("FPUTS ERROR"), -1);
		values++;
	}
	CHK2((fclose(fp) == EOF), free(filename), perror("FCLOSE ERROR"), -1);
	printf("Record Saved\n");
	free(filename);
	return (0);
}

char	**db_values(char *str)
{
	size_t	len;

	if (*str == '(')
		str++;
	len = strlen(str) - 1;
	if (str[len] == ')')
		str[len] = '\0';
	return (ft_strsplit(str, ','));
}
