/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:49:59 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/25 15:20:10 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNUMBER 12345

#include <ft_db.h>
int main(int argc, char *argv[])
{
	int			sockfd;
	int			newsockfd;
	int			portno;
	int			clilen;
	char			buffer[256];
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;
	int n;

	t_client		*client;
	client = db_client_init();
	db_msg(MSG_WELCOME);
	db_loop(client);

	CHK1((sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1, perror("ERROR SOCKET"), 0)
	bzero(serv_addr, sizeof(serv_addr));
	portno = PORTNUMBER;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	CHK1((bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) == -1, perror("ERROR BIND"), 0);
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	while (1)
	{
		CHK1((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1, perror("ERROR ACCEPT"), 0);
		bzero(buffer,256);
		CHK1((n = read(newsockfd, buffer, 255)) == -1, perror("ERROR READ"), 0);
		printf("Here is the message: %s\n",buffer);
	//	n = write(newsockfd,"I got your message",18);
	//	error("ERROR writing to socket");
	}
	return (0);
}
