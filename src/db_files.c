/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:35:33 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 12:29:50 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

void			file_del(void	*elm)
{
	if (elm == 0)
		return ; ft_strdel(&((t_db_file *)elm)->name);
	ft_strdel(&((t_db_file *)elm)->path);
	ft_strdel(&((t_db_file *)elm)->value);
	ft_bzero(elm, sizeof(t_db_file));
}

static int		db_ls(t_server *server)
{
	t_dir		*dp;
	t_db_file	*tmp;
	int			chk;
	DIR			*dirp;

	dirp = opendir(server->tblpath);
	CHK1(dirp == NULL, ERR("Open Dir Failed"), -1);
	while ((dp = readdir(dirp)) != 0)
	{
		if (dp->d_name[0] == '.')
			continue ;
		tmp = ft_memalloc(sizeof(t_db_file));
		CHK2(tmp == NULL, closedir(dirp), ERR("Malloc Failed"), -1);
		ft_asprintf(&tmp->path, "%s/%s", server->tblpath, dp->d_name);
		tmp->name = ft_strdup(dp->d_name);
		chk = lstat(tmp->path, &tmp->statinfo);
		CHK3(chk == -1, file_del(&tmp), closedir(dirp), ERR("Lstat Failed"), -1);
		arr_push(server->files, tmp);
	}
	closedir(dirp);
	return (0);
}

static int		db_readvalue(t_server *server)
{
	FILE			*fp;
	t_db_file		**tmp;
	int			i;
	int			readsize;
	
	CHK1(server->files == NULL, ERR("File Array not present"), -1);
	tmp = (t_db_file **)server->files->contents;
	i = 0;
	while (i < server->files->end)
	{
		fp = fopen(tmp[i]->path, "r");
		CHK1(fp == NULL, ERR("FOPEN ERROR"), -1);
		readsize = tmp[i]->statinfo.st_size + 1;
		tmp[i]->value = ft_strnew(readsize);
		CHK1(fgets(tmp[i]->value, readsize, fp) == NULL, ERR("FGETS ERROR"), -1);
		CHK1(fclose(fp) == EOF, ERR("FCLOSE ERROR"), -1);
		++i;
	}
	return (0);
}

static int		db_arrinit(t_server *server)
{
	t_arr		*files;

	files = arr_create(sizeof(t_db_file), PROTO_ARRAY_SIZE);
	CHK1(files == NULL, ERR("Array Create Failed"), -1);
	files->del = &file_del;
	server->files = files;
	return (0);
}

int			db_getfiles(t_server *server)
{
	int chk;

	if (server->files != NULL)
		arr_del(server->files);
	CHK(db_arrinit(server) == -1, -1);
	chk = db_ls(server);
	CHK1(((server->files->end == 0) || chk == -1), REPLY("No Records Found"), -1);
	CHK(db_readvalue(server) == -1, -1);
	return (0);
}
