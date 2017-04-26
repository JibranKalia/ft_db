/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 02:57:48 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 04:22:18 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_db.h"
#include <dirent.h>

DIR		*dir;
struct	dirent *ent;
t_list		**get_all(char *path)
{
	t_list	**all;
	t_list	*node;

	all = NULL;
	if ((dir = opendir (path)) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL)
		{
		    printf ("%s\n", ent->d_name);
			node = ft_lstnew(ent->d_name, 0);
			printf("Seg: %s\n", (char *)node->content);
			ft_lstappend(all, node);
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
	t_list	**list;
	t_list	*temp;
	int		fd;
	char	*t_path;
	char	*line;

	list = get_all(path);
	temp = *list;
	path = ft_strjoin(path, "/");
	while (temp)
	{
		if (strncmp(temp->content, ".", 1) != 0)
		{
			t_path = ft_strjoin(path, temp->content);//free later
			fd = open(t_path, O_RDONLY);
			get_next_line(fd, &line);
			printf("%s\n", line);
		}
		temp = temp->next;
	}
	close(fd);
}
