/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:35:21 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 21:26:03 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# include <ft_db.h>
# include <time.h>
# define LEN1 50000
# define LEN2 1000
# define IN_BUFF 1024
# define OUT_BUFF 1024 * 4

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct hostent		t_hostent;

typedef struct				s_db_client
{
	int						portno;
	int						sockfd;
	t_sockaddr_in			serv_addr;
	t_hostent				*server;
}							t_db_client;
int							write_buf(t_db_client *test, const char *fmt, ...);
int							read_buf(t_db_client *test, char *outbuf);
int							confirm_val(int i, const char *outbuf);
#endif
