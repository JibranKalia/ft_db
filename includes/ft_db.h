/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:21:49 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/26 17:21:08 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <libft.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <netinet/in.h>
# define PROTO_HASH_SIZE 10000000
# define DB_NAME_BUFF 50
# define PROTO_FUNC_NUM 7
# define PORTNUMBER 12345

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

typedef struct		s_server
{
	int				argc;
	char			*line;
	char			**args;
	int				fd;
	bool			flag_db_load;
	bool			flag_tbl_load;
	char			*dbpath;
	char			*tblpath;
	char			*logpath;
	size_t			hashsize;
	int				portno;
}					t_server;

/*
** INIT
*/

void				db_init();
t_server			*db_server_init(void);
void				db_server_clean(t_server *server);

/*
** DISPATCH
*/

int					db_load(t_server *server);
int					db_clear(t_server *server);
int					db_help(t_server *server);
int					db_set(t_server *server);
int					db_get(t_server *server);
int					db_delete(t_server *server);
int					db_exit(t_server *server);
int					db_exitclear(t_server *server);
int					db_loop(t_server *server, int sock);

int					db_dispatch(t_server *server);
void				db_split_line(t_server *server);

/*
** HASHTABLE
*/

uint32_t			db_murmurhash(const char *key, uint32_t len, uint32_t seed);
char				*db_gethash(t_server *server, const char *key);
char				*db_read_line(void);

/**
t_hashtable			*ht_create(int size);
char				*ht_get(t_hashtable *hashtable, char *key);
void				ht_set(t_hashtable *hashtable, char *key, void *value, int size);
**/
void 				ht_test();

/*
** MESSAGE
*/

#define MSG_WELCOME 1
#define MSG_HELP 2
#define MSG_DB_MISSING 3
#define MSG_TBL_MISSING 4
#define MSG_DELETE_USAGE 5
#define MSG_DELETE_USAGE2 6

int				db_msg(t_server *server, int code);
char			*cleanstr(char *str);
int				db_reply(t_server *server, const char *fmt, ...);

#endif
