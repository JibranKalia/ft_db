/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_test_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:42:37 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 19:00:10 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#define LEN1 3000
#define LEN2 1000
#define IN_BUFF 1024
#define OUT_BUFF 1024 * 4
#define EXITDB write_buf(test, "exit")

const char	g_charset[87] = "!#&'()*+-./0123456789;<=>?@ABCDFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnoprstuvwxyz{|}~";
char		g_data[LEN1][LEN2];

static void rand_string(char *str, size_t size)
{
	size_t		n;
	int			key;

	n = 0;
	--size;
	while (n < size)
	{
		key = rand() % (int)(sizeof(g_charset) - 1);
		str[n] = g_charset[key];
		++n;
	}
	str[size] = '\0';
}

static	int		write_buf(t_db_client *test, const char *fmt, ...)
{
	va_list		ap;
	int			n;
	char		inbuf[IN_BUFF];

	va_start(ap, fmt);
	bzero(inbuf, IN_BUFF);
	vsnprintf(inbuf, IN_BUFF, fmt, ap);
	n = write(test->sockfd, inbuf, strlen(inbuf));
	CHECK(n < 0, RETURN(-1), "ERROR writing to socket");
	va_end(ap);
	return (0);
}

static	int		read_buf(t_db_client *test, char *outbuf)
{
	va_list		ap;
	int			n;

	bzero(outbuf, OUT_BUFF);
	n = read(test->sockfd, outbuf, OUT_BUFF - 1);
	CHECK(n < 0, RETURN(-1), "ERROR reading from socket");
	outbuf[n] = 0;
	va_end(ap);
	return (0);
}

static	int		confirm_val(int i, const char *outbuf)
{
	char	*out;
	int		chk;

	out = strstr(outbuf, "VALUE:");
	CHECK(out == NULL, RETURN (-1), "Error: %s", outbuf);
	out += 7;
	chk = strncmp(out, g_data[i], strlen(g_data[i]));
	CHECK(chk != 0, RETURN(-1), "Incorrect Record.\nExpected = %s\nFound    = %s", g_data[i], out);
	if (chk == -1)
	{
		ft_printf("%{green}Test %d Failed.\nCorrect = %s\nRecieved = %s\n%{eoc}", i, g_data[i], out);
	}
	return (0);
}

static	int		start_test(t_db_client *test)
{
	char	outbuf[OUT_BUFF];
	int		i;

	write_buf(test, "LOAD --database db");
	read_buf(test, outbuf);
	write_buf(test,"LOAD --table test");
	read_buf(test, outbuf);
	write_buf(test,"delete --table");
	read_buf(test, outbuf);
	write_buf(test,"LOAD --table test");
	read_buf(test, outbuf);
	i = 0;
	while (i < LEN1)
	{
		rand_string(g_data[i], LEN2);
		++i;
	}
	i = 0;
	while (i < LEN1)
	{
		write_buf(test, "SET %d %s", i, g_data[i]);
		read_buf(test, outbuf);
		CHECK1(strncmp(outbuf, "Record Saved", 12) != 0, EXITDB, RETURN(-1), "Update Record Failed");
		++i;
	}
	i = 0;
	while (i < LEN1)
	{
		write_buf(test, "GET %d", i);
		read_buf(test, outbuf);
		CHK1(confirm_val(i, outbuf) == -1, EXITDB, -1);
		++i;
	}
	ft_printf("%{green}ALL Test %i Passed%{eoc}\n", i);
	EXITDB;
	return (0);
}

int		main(int argc, char **argv)
{
	t_db_client		*test;
	int				chk;

	test = ft_memalloc(sizeof(t_db_client));
	test->portno = (argc == 2) ? atoi(argv[1]) : 12345;
	test->server = gethostbyname("localhost");
	ft_printf("%{green}Portno = %d\n%{eoc}", test->portno);
	ft_printf("%{green}Hostname = %s\n%{eoc}", test->server->h_name);
	test->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(test->sockfd < 0, RETURN(-1), "Error Opening Socket");
	CHECK(test->server == NULL, RETURN(-1), "Error no such host");
	bzero(&test->serv_addr, sizeof(test->serv_addr));
	test->serv_addr.sin_family = AF_INET;
	memcpy((void *)test->server->h_addr,
			(void *)&test->serv_addr.sin_addr.s_addr,
			test->server->h_length);
	test->serv_addr.sin_port = htons(test->portno);
	chk = connect(test->sockfd, (struct sockaddr *)&test->serv_addr,
			sizeof(test->serv_addr));
	CHECK(chk < 0, RETURN(-1), "ERROR connecting");
	CHK(start_test(test) == -1, -1);
	return (0);
}
