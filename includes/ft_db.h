/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:21:49 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/22 21:13:31 by jkalia           ###   ########.fr       */
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
# define PROTO_HASH_SIZE 10000000
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
	bool			flag_tbl_load;
	char			*dbpath;
	char			*tblpath;
	char			*logpath;
	size_t			hashsize;
}					t_client;

/*
** INIT
*/

void				db_init();
t_client			*db_client_init(void);
void				db_client_clean(t_client *client);

/*
** DISPATCH
*/

int					db_load(t_client *client);
int					db_set(t_client *client);
int					db_get(t_client *client);
int					db_delete(t_client *client);
int					db_exit(t_client *client);
int					db_exitclear(t_client *client);
void				db_loop(t_client *client);

/*
** HASHTABLE
*/

uint32_t			db_murmurhash(const char *key, uint32_t len, uint32_t seed);
uint32_t			db_gethash(t_client *client, const char *key);
/**
t_hashtable			*ht_create(int size);
char				*ht_get(t_hashtable *hashtable, char *key);
void				ht_set(t_hashtable *hashtable, char *key, void *value, int size);
**/
void 				ht_test();

/*
** MESSAGE
*/

#define MSG_DB_MISSING 1
#define MSG_TBL_MISSING 2
void				db_msg(int code);

#endif
