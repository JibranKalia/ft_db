/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:21:49 by aakin-al          #+#    #+#             */
/*   Updated: 2017/05/03 18:43:51 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <netinet/in.h>

# define PROTO_HASH_SIZE 10000000
# define PROTO_ARRAY_SIZE 10
# define DB_NAME_BUFF 50
# define PORTNUMBER 12345
# define ERR(M) db_err(server, M)
# define REPLY(M, ...) db_reply(server, M, ##__VA_ARGS__)

/*
** MAIN STRUCT
*/

typedef struct		s_server
{
	int		argc;
	char		*line;
	char		**args;
	t_arr		*files;
	int		fd;
	bool		flag_db_load;
	bool		flag_tbl_load;
	char		*dbpath;
	char		*tblpath;
	char		*logpath;
	size_t		hashsize;
	int		portno;
}			t_server;

/*
** LSFILE
*/

typedef struct stat	t_stat;
typedef struct dirent	t_dir;
typedef struct		s_db_file
{
	char		*path;
	char		*name;
	char		*value;
	t_stat		statinfo;
}			t_db_file;
int			db_arrinit(t_server *server);
int			db_readvalue(t_server *server);
int			db_ls(t_server *server);

/*
** INIT
*/

void			db_init();
t_server		*db_server_init(void);
void			db_server_clean(t_server *server);

/*
** UTIL
*/

int			db_clear(t_server *server);
int			db_help(t_server *server);
int			db_delete(t_server *server);
int			db_exit(t_server *server);
int			db_exitclear(t_server *server);

/*
** DISPATCH
*/

int			db_loop(t_server *server, int sock);
int			db_dispatch(t_server *server);
char			*db_read_line(void);
void			db_split_line(t_server *server);

/*
** DISPATCH
*/

int			db_update(t_server *server);
int			db_set(t_server *server);

/*
** GET
*/

int			db_get(t_server *server);
int			db_get_print(t_server *server, FILE *fp, size_t size);
int			db_getall(t_server *server);

/*
** LOAD
*/

int			db_load(t_server *server);
int			db_loadtbl(t_server *server);
int			db_loaddb(t_server *server);

/*
** HASHTABLE
*/

char			*db_gethash(t_server *server, const char *key);

/*
** REPLY
*/

#define MSG_WELCOME 1
#define MSG_HELP 2
#define MSG_DB_MISSING 3
#define MSG_TBL_MISSING 4
#define MSG_DELETE_USAGE 5
#define MSG_DELETE_USAGE2 6

int			db_msg(t_server *server, int code);
int			db_err(t_server *server, const char *str);
int			db_reply(t_server *server, const char *fmt, ...);

#endif
