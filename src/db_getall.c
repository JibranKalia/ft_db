/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 14:47:08 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

void		file_del(void	*elm)
{
	if (elm == 0)
		return ;

	free(((t_ls_file *)elm)->name);
	free(((t_ls_file *)elm)->path);
	ft_bzero(elm, sizeof(t_ls_file));
}

/**
int8_t		ft_ls_print_dir(char *path)
{
	t_arr		*files;
	int			i;
	t_ls_file	**tmp;

	i = 0;
	files = arr_create(sizeof(t_ls_file), 100);
	CHECK(files == NULL, RETURN(-1), "Array Create Failed");
	files->del = &file_del;
	if (db_ls_get_dir(files, path, server) == -1)
	{
		//ft_dprintf(2, "ls: %s: %s\n", ls_pathname(path), strerror(errno));
		arr_del(files);
		return (-1);
	}
	CHECK1(files->end == 0, arr_del(files), RETURN (-1), "Get Dir Failed");
	tmp = (t_ls_file **)files->contents;
	while (i < files->end)
		printf("%s\n", tmp[i++]->name);
	arr_del(files);
	return (0);
}

t_list		*db_ls(char *path, t_server *server)
{
	t_list			*head;
	t_list			*node;
	char			*tmp;
	DIR				*dir;
	struct	dirent	*ent;

	head = ft_lstnew(NULL, 0);
	dir = opendir(path);
	CHK1(dir == NULL, ERR("OPENDIR ERROR"), NULL);
	while ((ent = readdir (dir)) != NULL)
	{
		tmp = strndup((char *)ent->d_name, ent->d_namlen);
		node = ft_lstnew(tmp, ent->d_namlen);
		ft_lstappend(&head, node);
	}
	closedir(dir);
	return (head);
}
**/

int			db_ls_get_dir(t_arr *files, char *path, t_server *server)
{
	t_dir		*dp;
	t_ls_file	*tmp;
	int			chk;
	DIR			*dirp;

	dirp = opendir(path);
	CHK1(dirp == NULL, ERR("Open Dir Failed"), -1);
	while ((dp = readdir(dirp)) != 0)
	{
		if (dp->d_name[0] == '.')
			continue ;
		tmp = ft_memalloc(sizeof(t_ls_file));
		CHK2(tmp == NULL, closedir(dirp), ERR("Malloc Failed"), -1);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name);
		tmp->name = ft_strdup(dp->d_name);
		chk = lstat(tmp->path, &tmp->statinfo);
		CHK3(chk == -1, file_del(&tmp), closedir(dirp), ERR("Lstat Failed"), -1);
		arr_push(files, tmp);
	}
	closedir(dirp);
	return (0);
}


int			db_getall(t_server *server)
{
	char			*filename;
	FILE			*fp;
	int				i;

	t_arr			*files;
	t_ls_file		**tmp;
	int				chk;

	files = arr_create(sizeof(t_ls_file), 100);
	CHK1(files == NULL, ERR("Array Create Failed"), -1);
	files->del = &file_del;
	chk = db_ls_get_dir(files, server->tblpath, server);
	CHK2((files->end == 0 || chk == -1), arr_del(files), ERR("Get Dir Failed"), -1);
	tmp = (t_ls_file **)files->contents;
	i = 0;
	while (i < files->end)
	{
		filename = tmp[i]->path;
		fp = fopen(tmp[i]->path, "r");
		CHK2(fp == NULL, free(filename), ERR("FOPEN ERROR"), -1);
		db_get_print(server, fp, tmp[i]->statinfo.st_size);
		CHK2(fclose(fp) == EOF, free(filename), db_err(server, "FCLOSE ERROR"), -1);
		++i;
	}
	arr_del(files);
	return (0);
}
