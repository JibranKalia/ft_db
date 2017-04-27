/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 16:43:32 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

t_list		*db_ls(char *path)
{
	t_list			*head;
	t_list			*node;
	char			*tmp;
	DIR				*dir;
	struct	dirent	*ent;

	head = ft_lstnew(NULL, 0);
	CHK1((dir = opendir(path)) == NULL, perror("OPENDIR ERROR"), NULL);
	while ((ent = readdir (dir)) != NULL)
	{
		tmp = strndup((char *)ent->d_name, ent->d_namlen);
		node = ft_lstnew(tmp, ent->d_namlen);
		ft_lstappend(&head, node);
	}
	closedir(dir);
	return (head);
}

int			db_getall(t_client *client)
{
	t_list			*list;
	t_list			*tmp;
	char			*filename;
	char			*path;
	FILE			*fp;
	int 			fd;
	struct stat		st;
	int				i;

	path = ft_strjoin(client->tblpath, "/");
	list = db_ls(path);
	tmp = list;
	i = 0;
	while (tmp)
	{
		if (tmp->content && strncmp(tmp->content, ".", 1) != 0 )
		{
			filename = ft_strjoin(path, tmp->content);
			CHK2(((fp = fopen(filename, "r")) == NULL), free(filename), perror("FOPEN ERROR"), -1);
			fd = fileno(fp);
			CHK2(fstat(fd, &st) == -1, free(filename), perror("FSTAT ERROR"), -1);
			db_get_print(fp, st.st_size * 2);
			CHK2(fclose(fp) == EOF, free(filename), perror("FCLOSE ERROR"), -1);
			++i;
		}
		tmp = tmp->next;
	}
	ft_lstfree(&list);
	if (i == 0)
		printf("No records found\n");
	return (0);
}

int			db_get_print(FILE *fp, size_t size)
{
	char	*buf;

	buf = (char *)malloc(size);
	bzero(buf, size);
	CHK2(fgets(buf, size, fp) == NULL, free(buf), perror("FGETS ERROR"), -1);
	printf("Record Value:\n%s\n", buf);
	free(buf);
	return (0);
}

int			db_get(t_client *client)
{
	char			*filename;
	FILE			*fp;
	int				fd;
	struct stat		st;

	CHK1(client->flag_db_load == false, db_msg(MSG_DB_MISSING), 0);
	CHK1(client->flag_tbl_load == false, db_msg(MSG_TBL_MISSING), 0);
	CHK1(client->argc != 2, printf("usage: GET key\n"), 0);
	if (strncasecmp(client->args[1], "all", 3) == 0)
		db_getall(client);
	else
	{
		filename = ft_strjoinf("/", db_gethash(client, client->args[1]), STRJOIN_FREE_SRC2);
		filename = ft_strjoinf(client->tblpath, filename, STRJOIN_FREE_SRC2);
		CHK2(((fp = fopen(filename, "r")) == NULL), free(filename), perror("FOPEN ERROR"), -1);
		fd = fileno(fp);
		CHK2(fstat(fd, &st) == -1, free(filename), perror("FSTAT ERROR"), -1);
		db_get_print(fp, st.st_size * 2);
		CHK2(fclose(fp) == EOF, free(filename), perror("FCLOSE ERROR"), -1);
		free(filename);
	}
	return (0);
}
