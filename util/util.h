/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:35:21 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 16:37:58 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>
#include <time.h>

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct hostent		t_hostent;

typedef struct				t_db_client
{
	int						portno;
	int						sockfd;
	t_sockaddr_in			serv_addr;
	t_hostent				*server;
}							t_db_client;
