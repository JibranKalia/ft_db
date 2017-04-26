/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:49:59 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/25 20:46:04 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PORTNUMBER 12345

#include <ft_db.h>

int		db_tcpparse(t_server *server)
{
	char		buffer[256];
	int			n;

	bzero(buffer, 256);
	CHK1((n = read(server->sockfd, buffer, 255)) == -1, perror("ERROR READ"), -1);
	printf("Here is the message: %s\n",buffer);
	CHK1((n = write(server->sockfd,"Message Recieved", 18)) == -1, perror("ERROR WRITE"), 0);
	server->line = strdup(buffer);
	db_split_line(server);
	db_dispatch(server);
	ft_tbldel(server->args);
	ft_strclr(server->line);
	return (0);
}

int		db_stdinparse(t_server *server)
{
	db_msg(MSG_WELCOME);
	while (1)
	{
		printf("> ");
		server->line = db_read_line();
		db_split_line(server);
		db_dispatch(server);
		ft_tbldel(server->args);
		ft_strclr(server->line);
	}
}

int		db_tcpbegin(t_server *server)
{
	int					pid;
	int					sockfd;
	int					newsockfd;
	int					portno;
	int					clilen;
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;

	CHK1((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1, perror("ERROR SOCKET"), -1)
	bzero((void *)&serv_addr, sizeof(serv_addr));
	portno = PORTNUMBER;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	CHK1((bind(sockfd, (struct sockaddr *)&serv_addr,
					sizeof(serv_addr))) == -1, perror("ERROR BIND"), -1);
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	while (1)
	{
		CHK1((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,
						(socklen_t *)&clilen)) == -1, perror("ERROR ACCEPT"), -1);
		CHK1((pid = fork()) == -1, perror("ERROR FORK"), -1);
		if (pid == 0)
		{
			close(sockfd);
			server->sockfd = newsockfd;
			CHK(db_tcpparse(server) == -1, -1);
			exit(EXIT_SUCCESS);
		}
		else
			close(newsockfd);
	}
}

int main(int argc, char **argv)
{
	t_server	*server;

	CHK1((argc != 2), printf("Usage: %s [stdin || tcp]", argv[0]), -1);
	server = db_server_init();
	if (strncasecmp(argv[1], "stdin", 5) == 0)
		db_stdinparse(server);
	else if (strncasecmp(argv[1], "tcp", 3) == 0)
		db_tcpbegin(server);
	else
		printf("Usage: %s [stdin || tcp]", argv[0]);
	db_server_clean(server);
	return (0);
}
