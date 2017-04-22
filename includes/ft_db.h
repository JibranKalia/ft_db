/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:21:49 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/22 13:01:13 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <libft.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <string.h>
# include <stdbool.h>
# define DB_NAME_BUFF 50
# define PROTO_FUNC_NUM 6


typedef struct		s_entry
{
	char			*key;
	void			*value;
	struct s_entry	*next;
}					t_entry;

typedef struct		s_hashtable
{
	int				size;
	t_entry			**table;
}					t_hashtable;

typedef struct		s_client
{
	int				argc;
	char			*line;
	char			**args;
	bool			flag_db_load;
	char			*dbpath;
}					t_client;

t_hashtable			*ht_create(int size);
char				*ht_get(t_hashtable *hashtable, char *key);
void				ht_set(t_hashtable *hashtable, char *key, void *value, int size);
void 				ht_test();

void				table_create(char *st);
void				db_init();
void				db_create();
int					db_load(t_client *client);
int					db_set(t_client *client);
int					db_get(t_client *client);
int					db_delete(t_client *client);
int					db_exit(t_client *client);
#endif
