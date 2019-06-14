/**********************************************************************
Program: <Ferry Loading>
Author: <Ariel Pena-Martinez>
Date: <03/10/2019>
Time spent: <8 hours>
Purpose: The purpose of this program is to determine the number of times
		 that a ferry must cross a river in order to serve all the waiting
		 cars from one side to the other.
Submission#: 23027958
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ferry.h"

void clear_keyboard_buffer(void);

int main(int argc, char *argv[])
{
    QUEUE hQ_left;
    QUEUE hQ_right;
    int test_cases;
    int length_of_ferry;
    int number_of_cars;
    int length_of_car;
    int river_count;
    int total_length_cars;
    char banks[10];
    Bank side;
    int i,j;

    hQ_left = queue_init_default();
    if(hQ_left == NULL)
    {
        printf("Failed to allocate space for queue\n");
		exit(1);
    }

    hQ_right = queue_init_default();
    if(hQ_right == NULL)
    {
        printf("Failed to allocate space for queue\n");
		exit(1);
    }

    scanf("%d",&test_cases);
    clear_keyboard_buffer();
    for(i=0; i<test_cases; i++)
    {
        scanf("%d %d", &length_of_ferry, &number_of_cars);
        clear_keyboard_buffer();
        length_of_ferry = length_of_ferry*100;

        for(j=0; j<number_of_cars; j++)
        {
            scanf("%d %s", &length_of_car, banks);
            if(banks[0] == 'l')
            {
                queue_enqueue(hQ_left, length_of_car);
            }
            else
            {
                queue_enqueue(hQ_right, length_of_car);
            }
        }

        river_count = 0;
        total_length_cars = 0;
        side = LEFT;

        while(!queue_empty(hQ_left) || !queue_empty(hQ_right))
        {
            if(side == LEFT)
            {
                total_length_cars = 0;
                while(!queue_empty(hQ_left) && total_length_cars + queue_front(hQ_left, NULL) <= length_of_ferry)
                {
                    total_length_cars += queue_front(hQ_left, NULL);
                    queue_service(hQ_left);
                }

                side = RIGHT;
                river_count++;
            }
            else
            {
                total_length_cars = 0;
                while(!queue_empty(hQ_right) && total_length_cars + queue_front(hQ_right, NULL) <= length_of_ferry)
                {
                    total_length_cars += queue_front(hQ_right, NULL);
                    queue_service(hQ_right);
                }

                side = LEFT;
                river_count++;
            }
        }

        printf("%d\n", river_count);
    }

    queue_destroy(&hQ_left);
    queue_destroy(&hQ_right);
    return 0;
}

void clear_keyboard_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
