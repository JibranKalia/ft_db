/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:36:35 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/21 23:06:20 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>
static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define test_cond(_c) if(_c) printf("\033[0;32mPASSED\033[0;0m\n"); else {printf("\033[0;31mFAILED\033[0;0m\n"); fails++;}
#define expect(_s, _c) { test(_s); test_cond(_c); }


typedef struct	teststruct {
	char strtest[16];        /* device strtest */
	float floattest;          /* floattest */
        /* char checksum;     /\* (reserved) checksum *\/ */
}				t_test;

void	ht_test()
{
        struct hashtable *ht = ht_create(65536);

        ht_set(ht, "key1", "inky", strlen("inky") + 1);
        ht_set(ht, "key2", "pinky", strlen("pingky") + 1);
        ht_set(ht, "key3", "blinky", strlen("blinky") + 1);
        ht_set(ht, "key4", "floyd", strlen("floyd") + 1);

        expect("hash key1 is inky", strcmp(ht_get(ht, "key1"), "inky") == 0);
        expect("hash key2 is pinky", strcmp(ht_get(ht, "key2"), "pinky") == 0);
        expect("hash key3 is blinky", strcmp(ht_get(ht, "key3"), "blinky") == 0);
        expect("hash key4 is floyd", strcmp(ht_get(ht, "key4"), "floyd") == 0);

        ht_set(ht, "key1", "new-inky", strlen("new-inky") + 1);
        ht_set(ht, "key2", "new-pinky", strlen("new-pinky") + 1);
        ht_set(ht, "key3", "new-blinky", strlen("new-blinky") + 1);
        ht_set(ht, "key4", "new-floyd", strlen("new-floyd") + 1);

        expect("hash key1 is new-inky", strcmp(ht_get(ht, "key1"), "new-inky") == 0);
        expect("hash key2 is new-pinky", strcmp(ht_get(ht, "key2"), "new-pinky") == 0);
        expect("hash key3 is new-blinky", strcmp(ht_get(ht, "key3"), "new-blinky") == 0);
        expect("hash key4 is new-floyd", strcmp(ht_get(ht, "key4"), "new-floyd") == 0);

        int n = 5;
        ht_set(ht, "key5", &n, sizeof(int)); n++;
        ht_set(ht, "key6", &n, sizeof(int)); n++;
        ht_set(ht, "key7", &n, sizeof(int)); n++;
        ht_set(ht, "key8", &n, sizeof(int)); n++;

        expect("hash key5 is 5", *ht_get(ht, "key5") == 5);
        expect("hash key6 is 6", *ht_get(ht, "key6") == 6);
        expect("hash key7 is 7", *ht_get(ht, "key7") == 7);
        expect("hash key8 is 8", *ht_get(ht, "key8") == 8);

        n = 50;
        ht_set(ht, "key5", &n, sizeof(int)); n++;
        ht_set(ht, "key6", &n, sizeof(int)); n++;
        ht_set(ht, "key7", &n, sizeof(int)); n++;
        ht_set(ht, "key8", &n, sizeof(int)); n++;

        expect("hash key5 is 50", *ht_get(ht, "key5") == 50);
        expect("hash key6 is 51", *ht_get(ht, "key6") == 51);
        expect("hash key7 is 52", *ht_get(ht, "key7") == 52);
        expect("hash key8 is 53", *ht_get(ht, "key8") == 53);

        t_test *data;
        t_test teststruct;

        strcpy(teststruct.strtest, "strtest");
        teststruct.floattest = 500.f;
        ht_set(ht, "key9", &teststruct, sizeof(teststruct));

        strcpy(teststruct.strtest, "strtest");
        teststruct.floattest = 1000.f;
        ht_set(ht, "key10", &teststruct, sizeof(teststruct));

        data = (struct teststruct*)ht_get(ht, "key9");
        expect("hash key9 strtest is strtest", strcmp(data->strtest, "strtest") == 0);
        expect("hash key9 floattest is 500.f", data->floattest == 500.f);

        data = (struct teststruct*)ht_get(ht, "key10");
        expect("hash key10 strtest is strtest", strcmp(data->strtest, "strtest") == 0);
        expect("hash key10 floattest is 1000.f", data->floattest == 1000.f);

        strcpy(teststruct.strtest, "new-strtest");
        teststruct.floattest = 5000.f;
        ht_set(ht, "key9", &teststruct, sizeof(teststruct));

        strcpy(teststruct.strtest, "new-strtest");
        teststruct.floattest = 10000.f;
        ht_set(ht, "key10", &teststruct, sizeof(teststruct));

        data = (struct teststruct*)ht_get(ht, "key9");
        expect("hash key9 strtest is new-strtest", strcmp(data->strtest, "new-strtest") == 0);
        expect("hash key9 floattest is 5000.f", data->floattest == 5000.f);

        data = (struct teststruct*)ht_get(ht, "key10");
        expect("hash key10 strtest is new-strtest", strcmp(data->strtest, "new-strtest") == 0);
        expect("hash key10 floattest is 10000.f", data->floattest == 10000.f);

        printf("Tests: %d, F: %d\n", tests, fails);
}
