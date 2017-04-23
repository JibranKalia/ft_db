/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:57:22 by jkalia            #+#    #+#             */
/*   Updated: 2017/04/22 20:39:15 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Simple Hash C implementation
** Copyright (c) 2012 Tony Thompson
** <tony@thompson.name>
*/

#include <ft_db.h>

/*
** Create a new hashtable
** Allocate table (line 16)
** Allocate pointers to head node (line 21)
*/

t_hashtable	*ht_create(int size)
{
	t_hashtable	*hashtable;
	int			i;

	i = 0;
	hashtable = NULL;
	CHK(size < 1, NULL);
	CHK((hashtable = ft_memalloc(sizeof(t_hashtable))) == NULL, NULL);
	CHK1((hashtable->table = ft_memalloc(sizeof(t_entry*) * size)) == NULL, free(hashtable), NULL)
	while (i < size)
	{
		hashtable->table[i] = NULL;
		++i;
	}
	hashtable->size = size;
	return (hashtable);
}

/*
** Hash a string for specific hash table
** Conver string to integer (line 39)
*/

int			ht_hash(t_hashtable *hashtable, char *key)
{
	uint32_t	seed;
	uint32_t	hashval;
	
	seed = 12345678;
	hashval = murmurhash(key, (uint32_t)strlen(key), seed);
	printf("%d\n", hashtable->size);
	return (hashval % hashtable->size);
}

/*
** Create a key-value pair
*/

t_entry		*ht_newpair(char *key, void *value, int size)
{
	t_entry *newpair;

	if ((newpair = malloc(sizeof(t_entry))) == NULL)
		return (NULL);
	if ((newpair->key = strdup(key)) == NULL)
		return (NULL);
	CHK((newpair->value = ft_memalloc(size)) == NULL, NULL)
	memcpy(newpair->value, value, size);
	newpair->next = NULL;
	return (newpair);
}

/*
** Insert a key-value pair.
** There is already a pair. Replace that string (line 86)
** If not create a pair. (line 92)
** Start of Linked list (line 96)
** End of Linked list (line 102)
** Middle of linked list (line 104)
*/

void		ht_set(t_hashtable *hashtable, char *key, void *value, int size)
{
	int		bin;
	t_entry	*newpair;
	t_entry	*next;
	t_entry	*last;

	bin = ht_hash(hashtable, key);
	next = hashtable->table[bin];
	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
	{
		free(next->value);
		next->value = ft_memalloc(size);
		memcpy(next->value, value, size);
	}
	else
	{
		newpair = ht_newpair(key, value, size);
		if (next == hashtable->table[bin])
		{
			newpair->next = next;
			hashtable->table[bin] = newpair;
		}
		else if (next == NULL)
			last->next = newpair;
		else
		{
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/*
** Retrieve a key-value pair from hash table
** Step through the bin looking for value (line 125)
** Did we find anything? (line 129)
*/

char		*ht_get(t_hashtable *hashtable, char *key)
{
	int		bin;
	t_entry	*pair;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
	{
		pair = pair->next;
	}
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
		return (NULL);
	else
		return (pair->value);
}
