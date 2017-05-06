/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_test_buff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:21:26 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 21:27:44 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

extern char	g_data[LEN1][LEN2];

int			write_buf(t_db_client *test, const char *fmt, ...)
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

int			read_buf(t_db_client *test, char *outbuf)
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

int			confirm_val(int i, const char *outbuf)
{
	char	*out;
	int		chk;

	out = strstr(outbuf, "VALUE:");
	CHECK(out == NULL, RETURN(-1), "Error: %s", outbuf);
	out += 7;
	chk = strncmp(out, g_data[i], strlen(g_data[i]));
	CHECK(chk != 0, RETURN(-1), "Incorrect Record.", g_data[i], out);
	if (chk == -1)
	{
		ft_printf("%{green}Test %d Failed.", i, g_data[i], out);
	}
	return (0);
}
