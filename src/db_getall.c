/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 15:46:11 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

void		file_del(void	*elm)
{
	if (elm == 0)
		return ;
	ft_strdel(&((t_db_file *)elm)->name);
	ft_strdel(&((t_db_file *)elm)->path);
	ft_strdel(&((t_db_file *)elm)->value);
	ft_bzero(elm, sizeof(t_db_file));
}

int			db_get_all_print(t_server *server, t_arr *files)
{
	char			*buf;
	int				len = 0;
	int				i = 0, j = 0, k = 0;
	t_db_file		**tmp;
	
	tmp = (t_db_file **)files->contents;
	while (i < files->end)
	{
		len += tmp[i]->statinfo.st_size + 10;
		++i;
	}
	buf = ft_strnew(len);
	i = 0;
	while (i < files->end)
	{
		k = strlen(tmp[i]->value);
		memcpy(&buf[j], "VALUE: ", 7);
		j += 7;
		memcpy(&buf[j], tmp[i]->value, k);
		j += k;
		memcpy(&buf[j], "\n", 1);
		++j;
		++i;
	}
	db_reply(server, buf);
	free(buf);
	return (0);
}

int			db_ls_get_dir(t_arr *files, char *path, t_server *server)
{
	t_dir		*dp;
	t_db_file	*tmp;
	int			chk;
	DIR			*dirp;

	dirp = opendir(path);
	CHK1(dirp == NULL, ERR("Open Dir Failed"), -1);
	while ((dp = readdir(dirp)) != 0)
	{
		if (dp->d_name[0] == '.')
			continue ;
		tmp = ft_memalloc(sizeof(t_db_file));
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
	FILE			*fp;
	int				readsize;
	t_arr			*files;
	t_db_file		**tmp;
	int				chk;
	int				i;

	files = arr_create(sizeof(t_db_file), 100);
	CHK1(files == NULL, ERR("Array Create Failed"), -1);
	files->del = &file_del;
	chk = db_ls_get_dir(files, server->tblpath, server);
	CHK2((files->end == 0 || chk == -1), arr_del(files), ERR("Get Dir Failed"), -1);
	tmp = (t_db_file **)files->contents;
	i = 0;
	while (i < files->end)
	{
		fp = fopen(tmp[i]->path, "r");
		CHK2(fp == NULL, ERR("FOPEN ERROR"), arr_del(files), -1);
		readsize = tmp[i]->statinfo.st_size;
		tmp[i]->value = ft_strnew(readsize);
		CHK2(fgets(tmp[i]->value, readsize, fp) == NULL, ERR("FGETS ERROR"), arr_del(files), -1);
		CHK2(fclose(fp) == EOF, ERR("FCLOSE ERROR"), arr_del(files), -1);
		++i;
	}
	db_get_all_print(server, files);
	arr_del(files);
	return (0);
}
