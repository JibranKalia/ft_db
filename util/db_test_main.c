/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_test_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:42:37 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 16:45:43 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#define LEN1 100
#define LEN2 100

static char *rand_string(char *str, size_t size)
{
	size_t		n;
	int			key;

	n = 0;
	const char charset[90] = "!#%&'()*++--./012345678 9;<=>?@ABCDFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnoprstuvwxyz{|}~";
	--size;
	while (n < size)
	{
		key = rand() % (int) (sizeof charset - 1);
		str[n] = charset[key];
		++n;
	}
	str[size] = '\0';
	return (str);
}

static	int		start_test(t_db_client *test)
{
	char	data[LEN1][LEN2];
	char	buffer[BUFF_SIZE];
	char	*out;
	int		i;
	int		n;

	bzero(buffer, BUFF_SIZE);
	snprintf(buffer, BUFF_SIZE, "LOAD --database db");
	n = write(test->sockfd, buffer, strlen(buffer));
//	DEBUG("Print = {%s}", buf);
	CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
	bzero(buffer, BUFF_SIZE);
	n = read(test->sockfd, buffer, 1024 * 4);
	bzero(buffer, BUFF_SIZE);
	snprintf(buffer, BUFF_SIZE, "LOAD --table test");
	n = write(test->sockfd, buffer, strlen(buffer));
//	DEBUG("Print = {%s}", buf);
	bzero(buffer, BUFF_SIZE);
	n = read(test->sockfd, buffer, 1024 * 4);
	CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
	bzero(buffer, BUFF_SIZE);
	i = 0;
	while (i < LEN1)
	{
		rand_string(data[i], 10);
		++i;
	}
	i = 0;
	while (i < LEN1)
	{
		bzero(buffer, BUFF_SIZE);
		snprintf(buffer, 1024, "SET %d %s", i, data[i]);
		n = write(test->sockfd, buffer, strlen(buffer));
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		bzero(buffer, BUFF_SIZE);
		bzero(buffer, 1024 * 4);
		n = read(test->sockfd, buffer, 1024 * 4);
		CHECK(n < 0, RETURN(-1), "ERROR reading from socket");
		//CHECK(strncmp(buffer, "Record Updated", 12) != 0, RETURN(-1), "Error Saving Record");
		++i;
	}

	i = 0;
	while (i < LEN1)
	{
		bzero(buffer, 1024 * 4);
		snprintf(buffer, 1024, "GET %d", i);
		n = write(test->sockfd, buffer, strlen(buffer));
		CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
		bzero(buffer, 1024 * 4);
		n = read(test->sockfd, buffer, 1024 * 4);
		CHECK(n < 0, RETURN(-1), "ERROR reading from socket");
		out = strstr(buffer, data[i]);
		CHECK(out == NULL, RETURN (-1), "String not found Record. Expected = %s\nFound = %s", data[i], buffer);
		CHECK(strncmp(out, data[i], LEN2) != 0, RETURN(-1), "Incorrect Record. Expected = %s. Found = %s", data[i], buffer);
		++i;
	}
	return (0);

}

int main(int argc, char **argv)
{
	t_db_client	*test;

	int			chk;
	test = ft_memalloc(sizeof(t_db_client));
	if (argc == 2)
		test->portno = atoi(argv[1]);
	else
		test->portno = 12345;
	test->server = gethostbyname("localhost");
	ft_printf("%{green}Portno = %d\n%{eoc}", test->portno);
	ft_printf("%{green}Hostname = %s\n%{eoc}", test->server->h_name);
	test->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(test->sockfd < 0, RETURN(-1), "Error Opening Socket");
	CHECK(test->server == NULL, RETURN(-1), "Error no such host");
	bzero(&test->serv_addr, sizeof(test->serv_addr));
	test->serv_addr.sin_family = AF_INET;
	memcpy((void *)test->server->h_addr, (void *)&test->serv_addr.sin_addr.s_addr, test->server->h_length);
	test->serv_addr.sin_port = htons(test->portno);
	chk = connect(test->sockfd, (struct sockaddr *)&test->serv_addr, sizeof(test->serv_addr));
	CHECK(chk < 0, RETURN (-1), "ERROR connecting");
	CHK(start_test(test) == -1, -1);
	return (0);
}
