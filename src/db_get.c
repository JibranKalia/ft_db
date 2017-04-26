/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 16:22:22 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

DIR		*dir;
struct	dirent *ent;
t_list		*db_ls(char *path)
{
	t_list	*all;
	t_list	*node;
	char	*tmp;

	all = ft_lstnew(NULL, 0);
	if ((dir = opendir(path)) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL)
		{
		    //printf ("%s\n", ent->d_name);
			tmp = strndup((char *)ent->d_name, ent->d_namlen);
		   	node = ft_lstnew(tmp, ent->d_namlen);
			//printf("Seg: {%s}, CS: %zu\n", (char *)node->content, node->content_size);
			ft_lstappend(&all, node);
			//printf("Seg Here2?\n");
		}
  		closedir (dir);
	} 
	else 
	{
	  /* could not open directory */
	  perror ("");
	  exit(1); //more appropriate exit required!!!
	}
	return (all);
}

int			db_getall(t_client *client)
{
	t_list			*list;
	t_list			*temp;
	char			*filename;
	char			*path;
	FILE			*fp;
	int 			fd;
	struct stat		st;

	path = ft_strjoin(client->tblpath, "/");
	list = db_ls(path);
	temp = list;
	while (temp)
	{
		if (temp->content && strncmp(temp->content, ".", 1) != 0 )
		{
			filename = ft_strjoin(path, temp->content);
			CHK2(((fp = fopen(filename, "r")) == NULL), free(filename), perror("FOPEN ERROR"), -1);
			fd = fileno(fp);
			CHK2(fstat(fd, &st) == -1, free(filename), perror("FSTAT ERROR"), -1);
			db_get_print(fp, st.st_size * 2);
			CHK2(fclose(fp) == EOF, free(filename), perror("FCLOSE ERROR"), -1);
		}
		temp = temp->next;
	}
	ft_lstfree(&list);
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
