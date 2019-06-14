#include <stdio.h>
#include <stdlib.h>
#include "ferry.h"


struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
	Node* prev;
};

struct queue
{
	Node* head;
	Node* tail;
};
typedef struct queue Queue;

QUEUE queue_init_default(void)
{
	Queue* pQ;
	pQ = (Queue*)malloc(sizeof(Queue));
	if (pQ != NULL)
	{
		pQ->head = NULL;
		pQ->tail = NULL;
	}
	return (QUEUE)pQ;
}

Status queue_enqueue(QUEUE hQ, int item)
{
	Queue* pQ = (Queue*)hQ;
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));

	if (temp == NULL)
    {
        return FAILURE;
    }

    temp->data = item;
    temp->next = NULL;
    temp->prev = NULL;

    if(pQ->head == NULL || pQ->tail == NULL)
    {
        pQ->head = temp;
        pQ->tail = temp;
    }
    else
    {
        pQ->tail->next = temp;
        temp->prev = pQ->tail;
        pQ->tail = temp;
    }

	return SUCCESS;
}

Status queue_service(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	Node* temp;

	if (queue_empty(hQ))
	{
		return FAILURE;
	}

	temp = pQ->head;
	pQ->head = pQ->head->next;
	free(temp);

	if(pQ->head != NULL)
    {
        pQ->head->prev = NULL;
    }

	return SUCCESS;
}

int queue_front(QUEUE hQ, Status* pStatus)
{
	Queue* pQ = (Queue*)hQ;
	if (queue_empty(hQ))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -1337;
	}

	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}

	return pQ->head->data;
}

Boolean queue_empty(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;

	return (Boolean)(pQ->head == NULL);
}

void queue_destroy(QUEUE* phQueue)
{
	Queue* pQ = (Queue*)*phQueue;
	Node* head = pQ->head;
	Node* temp;

	while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    free(pQ);
	*phQueue = NULL;
}
