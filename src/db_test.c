/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:36:35 by aakin-al          #+#    #+#             */
/*   Updated: 2017/04/21 19:55:58 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>
static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define test_cond(_c) if(_c) printf("\033[0;32mPASSED\033[0;0m\n"); else {printf("\033[0;31mFAILED\033[0;0m\n"); fails++;}
#define expect(_s, _c) { test(_s); test_cond(_c); }


struct gvtData {
        char version[7];      /* protocol version */
        char imei[16];        /* device IMEI */
        char name[16];        /* device name */
        char RS;              /* GPRS real-time/stored data flag */
        char date[7];         /* date */
        char time[7];         /* time */
        char fixable;         /* GPS fixed flag */

        char latitude[11];    /* latitude */
        char NS;              /* north or south */
        char longitude[13];   /* longitude */
        char WE;              /* west or east? */

        char usedBds[3];      /* used satellite number of BDS */
        char usedGps[3];      /* used satellite number of GPS */
        char usedGlonass[3];  /* used satellite number of GLONASS */

        float hdop;           /* HDOP */
        float speed;          /* speed */
        float course;         /* course */
        float altitude;       /* altitude */
        float mileage;        /* mileage */

        char mcc[4];          /* Mobile country code. */
        char mnc[3];          /* Mobile network code. */
        char lac[5];          /* Location area code */
        char cellId[5];       /* Cell ID */
        char gsmSignal;       /* GSM signal strength */
        char digitalInFlags;  /* digital input */
        char digitalOutFlags; /* digital output */
        short analog1;        /* analog input 1 */
        short analog2;        /* analog input 2 */
        short analog3;        /* analog input 3 */
        float temperature1;   /* temperature sensor 1 */
        float temperature2;   /* temperature sensor 2 */
        /* char rfid;         /\* (reserved) RFID *\/ */
        /* char external;     /\* (reserved) external accessories status *\/ */
        char battery;         /* battery level */
        char alert[25];       /* alert event type */
        /* char checksum;     /\* (reserved) checksum *\/ */
};

void	start()
{
	int		ret;

	printf("Enter number to select option\n1.\tCreate New DB\n2.\tLoad Existing DB\n3.\tExit.\n");
	scanf("%d", &ret);
	if (ret == 1)
		db_create();
	else if (ret == 2)
		db_load();
	else if (ret == 3)
		exit(1);
	else
	{
		printf("Enter a number between 1 and 3\n");
		start();
	}
}

void test_hashtable()
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

        struct gvtData *data;
        struct gvtData gvtData;

        strcpy(gvtData.imei, "IMEI");
        gvtData.speed = 500.f;
        ht_set(ht, "key9", &gvtData, sizeof(gvtData));

        strcpy(gvtData.imei, "imei");
        gvtData.speed = 1000.f;
        ht_set(ht, "key10", &gvtData, sizeof(gvtData));

        data = (struct gvtData*)ht_get(ht, "key9");
        expect("hash key9 imei is IMEI", strcmp(data->imei, "IMEI") == 0);
        expect("hash key9 speed is 500.f", data->speed == 500.f);

        data = (struct gvtData*)ht_get(ht, "key10");
        expect("hash key10 imei is imei", strcmp(data->imei, "imei") == 0);
        expect("hash key10 speed is 1000.f", data->speed == 1000.f);

        strcpy(gvtData.imei, "new-IMEI");
        gvtData.speed = 5000.f;
        ht_set(ht, "key9", &gvtData, sizeof(gvtData));

        strcpy(gvtData.imei, "new-imei");
        gvtData.speed = 10000.f;
        ht_set(ht, "key10", &gvtData, sizeof(gvtData));

        data = (struct gvtData*)ht_get(ht, "key9");
        expect("hash key9 imei is new-IMEI", strcmp(data->imei, "new-IMEI") == 0);
        expect("hash key9 speed is 5000.f", data->speed == 5000.f);

        data = (struct gvtData*)ht_get(ht, "key10");
        expect("hash key10 imei is new-imei", strcmp(data->imei, "new-imei") == 0);
        expect("hash key10 speed is 10000.f", data->speed == 10000.f);
}

int main(int argc, char **argv)
{
        test_hashtable();

        printf("Tests: %d, F: %d\n", tests, fails);
        return 0;
}
