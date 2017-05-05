/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_murmurhash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:32:13 by jkalia            #+#    #+#             */
/*   Updated: 2017/05/05 13:39:38 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** `murmurhash.h' - murmurhash
**
** copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
*/

#include <ft_db.h>

uint32_t	db_murmurhash(const char *key, uint32_t len, uint32_t seed)
{
	uint32_t		c1;
	uint32_t		c2;
	uint32_t		r1;
	uint32_t		r2;
	uint32_t		m;
	uint32_t		n;
	uint32_t		h;
	uint32_t		k;
	uint8_t			*d;
	const uint32_t	*chunks;
	const uint8_t	*tail;
	int				i;
	int				l;

	c1 = 0xcc9e2d51;
	c2 = 0x1b873593;
	r1 = 15;
	r2 = 13;
	m = 5;
	n = 0xe6546b64;
	h = 0;
	k = 0;
	d = (uint8_t *)key;
	chunks = NULL;
	tail = NULL;
	i = 0;
	l = len / 4;
	h = seed;
	chunks = (const uint32_t *)(d + l * 4);
	tail = (const uint8_t *)(d + l * 4);
	i = -l;
	while (i != 0)
	{
		k = chunks[i];
		k *= c1;
		k = (k << r1) | (k >> (32 - r1));
		k *= c2;
		h ^= k;
		h = (h << r2) | (h >> (32 - r2));
		h = h * m + n;
		++i;
	}
	k = 0;
	switch (len & 3)
	{
		case 3:
		k ^= (tail[2] << 16);
		case 2:
		k ^= (tail[1] << 8);
		case 1:
		k ^= tail[0];
		k *= c1;
		k = (k << r1) | (k >> (32 - r1));
		k *= c2;
		h ^= k;
	}
	h ^= len;
	h ^= (h >> 16);
	h *= 0x85ebca6b;
	h ^= (h >> 13);
	h *= 0xc2b2ae35;
	h ^= (h >> 16);
	return (h);
}

char		*db_gethash(t_server *server, const char *key)
{
	uint32_t	seed;
	uint32_t	hash;
	uint32_t	out;
	char		*filename;

	if (server->hashsize == 0)
		server->hashsize = PROTO_HASH_SIZE;
	seed = 123456789;
	hash = db_murmurhash(key, (uint32_t)strlen(key), seed);
	out = hash % server->hashsize;
	filename = ft_itoa_base(out, 10, "0123456789");
	return (filename);
}
