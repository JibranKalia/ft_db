/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 14:21:16 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_db.h"
#include <dirent.h>

DIR		*dir;
struct	dirent *ent;
t_list		*get_all(char *path)
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

int		db_all(char *path)
{
	t_list	*list;
	t_list	*temp;
	char		*filename;
	FILE		*fp;
	int 		fd;
	struct stat	st;

	list = get_all(path);
	temp = list;
	while (temp)
	{
		if (temp->content && strncmp(temp->content, ".", 1) != 0 )
		{
			filename = ft_strjoin(path, temp->content);//free later
			CHK2(((fp = fopen(filename, "r")) == NULL), free(filename), perror("FOPEN ERROR"), -1);
			fd = fileno(fp);
			CHK2(fstat(fd, &st) == -1, free(filename), perror("FSTAT ERROR"), -1);
			db_get_print(fp, st.st_size * 2);
			CHK2(fclose(fp) == EOF, free(filename), perror("FCLOSE ERROR"), -1);
		}
		temp = temp->next;
	}
	free(list);
	list = NULL;
	free(temp);
	temp = NULL;
	return (0);
}
