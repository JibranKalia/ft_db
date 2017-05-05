/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_client_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:23:52 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 15:40:33 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int main(int argc, char **argv)
{
	int			sockfd;
	int			chk;
	int			portno;
	int			n;
	struct sockaddr_in	serv_addr;
	struct hostent 		*server;
	char			buffer[1024 * 4];
	
	DEBUG("ARGC = %d", argc);

	if (argc == 3)
	{
		server = gethostbyname(argv[1]);
		portno = atoi(argv[2]);
		ft_printf("%{green}Portno = %d\n%{eoc}", portno);
		ft_printf("%{green}Hostname = %s\n%{eoc}", server->h_name);
	}
	else if (argc == 2)
	{
		portno = atoi(argv[1]);
		server = gethostbyname("localhost");
		ft_printf("%{green}Portno = %d\n%{eoc}", portno);
		ft_printf("%{green}Hostname = %s\n%{eoc}", server->h_name);
	}
	else
	{
		portno = 12345;
		server = gethostbyname("localhost");
		ft_printf("%{green}Portno = %d\n%{eoc}", portno);
		ft_printf("%{green}Hostname = %s\n%{eoc}", server->h_name);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(sockfd < 0, RETURN(-1), "Error Opening Socket");
	CHECK(server == NULL, RETURN(-1), "Error no such host");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((void *)server->h_addr, (void *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	chk = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	CHECK(chk < 0, RETURN (-1), "ERROR connecting");

	while (1)
	{
		printf("> ");
		bzero(buffer, 1024 * 4);
		fgets(buffer, 256, stdin);
		if (strncmp(buffer, "exit", 5) == 0)
			exit(1);
		n = write(sockfd, buffer, strlen(buffer));
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		bzero(buffer, 256);
		n = read(sockfd, buffer, 1024 * 4);
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		printf("%s\n",buffer);
	}
	return (0);
}
