/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 14:05:33 by aakin-al         ###   ########.fr       */
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

void		db_all(char *path)
{
	t_list	*list;
	t_list	*temp;
	int		fp;
	char	*t_path;
	char	*line;

	printf("Path = %s\n", path);
	list = get_all(path);
	temp = list;
	while (temp)
	{
		if (temp->content && strncmp(temp->content, ".", 1) != 0)
		{
			t_path = ft_strjoin(path, temp->content);//free later
			printf("%s\n", temp->content);
			fd = open(t_path, O_RDONLY);
			get_next_line(fd, &line);
			printf("FILE: %s\n", line);
			free(line);
		}
		temp = temp->next;
	}
	close(fd);
}
