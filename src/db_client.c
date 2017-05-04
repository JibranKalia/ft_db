#include <ft_db.h>

int main(int argc, char **argv)
{
	int			sockfd;
	int			chk;
	int			portno;
//	int			n;
	struct sockaddr_in	serv_addr;
	struct hostent 		*server;
//	char			buffer[1024 * 4];

	if (argc == 2)
		portno = atoi(argv[1]);
	else
		portno = 12345;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(sockfd < 0, RETURN(-1), "Error Opening Socket");
	server = gethostbyname("localhost");
	CHECK(server == NULL, RETURN(-1), "Error no such host");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((void *)server->h_addr, (void *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	chk = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	CHECK(chk < 0, RETURN (-1), "ERROR connecting");

	/**
	while (1)
	{
		printf("> ");
		bzero(buffer, 1024 * 4);
		fgets(buffer, 256, stdin);
		if (strncmp(buffer, "exit", 5) == 0)
			exit (1);
		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
			error("ERROR writing to socket");
		bzero(buffer, 256);
		n = read(sockfd, buffer, 1024 * 4);
		if (n < 0)
			error("ERROR reading from socket");
		printf("%s\n",buffer);
	}
	**/
	return (0);
}
