/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_client_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:23:52 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 17:08:28 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

static int	client_loop(t_db_client *client)
{
	char			buffer[BUFF_SIZE];
	int				n;

	while (1)
	{
		printf("> ");
		bzero(buffer, BUFF_SIZE);
		fgets(buffer, BUFF_SIZE, stdin);
		if (strncmp(buffer, "exit", 5) == 0)
			exit(1);
		n = write(client->sockfd, buffer, strlen(buffer));
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		bzero(buffer, BUFF_SIZE);
		n = read(client->sockfd, buffer, BUFF_SIZE);
		n = write(client->sockfd, buffer, strlen(buffer));
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		printf("%s\n", buffer);
		bzero(buffer, BUFF_SIZE);
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
	}
	return (0);
}

static int	client_connect(t_db_client *client)
{
	int				chk;

	ft_printf("%{green}Portno = %d\n%{eoc}", client->portno);
	ft_printf("%{green}Hostname = %s\n%{eoc}", client->server->h_name);
	client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(client->sockfd < 0, RETURN(-1), "Error Opening Socket");
	CHECK(client->server == NULL, RETURN(-1), "Error no such host");
	bzero(&client->serv_addr, sizeof(client->serv_addr));
	client->serv_addr.sin_family = AF_INET;
	memcpy((void *)client->server->h_addr,
			(void *)&client->serv_addr.sin_addr.s_addr,
			client->server->h_length);
	client->serv_addr.sin_port = htons(client->portno);
	chk = connect(client->sockfd, (struct sockaddr *)&client->serv_addr,
			sizeof(client->serv_addr));
	CHECK(chk < 0, RETURN(-1), "ERROR connecting");
	CHK(client_loop(client) == -1, -1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_db_client		*client;

	client = ft_memalloc(sizeof(t_db_client));
	if (argc == 3)
	{
		client->server = gethostbyname(argv[1]);
		client->portno = atoi(argv[2]);
	}
	else if (argc == 2)
	{
		client->portno = atoi(argv[1]);
		client->server = gethostbyname("localhost");
	}
	else
	{
		client->portno = 12345;
		client->server = gethostbyname("localhost");
	}
	CHK(client_connect(client) == -1, -1);
	return (0);
}
