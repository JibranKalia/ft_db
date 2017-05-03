/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_getall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:09:48 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/03 13:58:34 by jkalia           ###   ########.fr       */
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


int8_t		ft_ls_get_dir(t_arr *files, char *path)
{
	t_dir		*dp;
	t_ls_file	*tmp;
	int			chk;
	DIR			*dirp;

	dirp = opendir(path);
	CHECK(dirp == NULL, RETURN(-1), "Open Dir Failed");
	while ((dp = readdir(dirp)) != 0)
	{
		if (dp->d_name[0] == '.' && !(g_ls_flags & FLG_a))
			continue ;
		tmp = ft_memalloc(sizeof(t_ls_file));
		CHECK1(tmp == NULL, closedir(dirp), RETURN(-1), "Malloc Failed");
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name);
		tmp->name = ft_strdup(dp->d_name);
		chk = lstat(tmp->path, &tmp->statinfo);
		CHECK2(chk == -1, file_del(&tmp), closedir(dirp), RETURN(-1), "Lstat Failed");
		arr_push(files, tmp);
	}
	closedir(dirp);
	return (0);
}

int8_t		ft_ls_print_dir(char *path)
{
	t_arr		*files;
	size_t		i;
	t_ls_file	**tmp;

	i = 0;
	files = arr_create(sizeof(t_ls_file), 100);
	CHECK(files == NULL, RETURN(-1), "Array Create Failed");
	files->del = &file_del;
	if (ft_ls_get_dir(files, path) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", ls_pathname(path), strerror(errno));
		arr_del(files);
		return (-1);
	}
	CHECK1(files->end == 0), arr_del(files), RETURN (-1), "Get Dir Failed");
	//arr_qsort(files, testcmp);
	tmp = (t_ls_file **)files->contents;
	while (i < files->end)
		printf("%s\n", tmp[i++]->name);
	arr_del(files);
	return (0);
}
