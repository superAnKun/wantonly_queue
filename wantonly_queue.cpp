#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Queue
{
	void* data;
	int head, tail;
	int size, count, grain;
} Queue; 

#define init(T) (__init(sizeof(T), 2))
#define push(q, val) (__push(&q, &val))
#define pop(q) (__pop(q))
#define front(q, T) (*((T*)__front(q)))

Queue* __init(int grain, int size)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->data = (void*)malloc(sizeof(char) * grain * size);
	queue->size = size;
	queue->grain = grain;
	queue->count = 0;
	queue->head = 0;
	queue->tail = 0;
	return queue;
}

void* __front(Queue*);
int __push(Queue**, void*);
int empty(Queue*);
int __pop(Queue*);
void clear(Queue*);
Queue* expand(Queue* queue)
{
	Queue* q = __init(queue->grain, queue->size * 2);
	while (!empty(queue))
	{
		__push(&q, __front(queue));
		pop(queue);
	}
	clear(queue);
	return q;
}


int __push(Queue** q, void* src)
{
	Queue* queue = *q;
	if (queue == NULL) return 0;
	if (queue->count >= queue->size)
	{
		*q = expand(queue);
		queue = *q;
		if (!queue) return 0;
	}
	
	//if (queue->count >= queue->size) return 0;
	memcpy(queue->data + queue->head * queue->grain, src, queue->grain);
	++queue->head %= queue->size;
	queue->count++;
	return 1;
}

int __pop(Queue* queue)
{
	if (queue == NULL) return 0;
	if (queue->count <= 0) return 0;
	++queue->tail %= queue->size;
	queue->count--;
	return 1;
}

void* __front(Queue* queue)
{
	memset(ret, 0, queue->grain + 1);
	if (queue == NULL) return ret;
	if (queue->count <= 0) return ret;
	return queue->data + queue->tail * queue->grain;
}

int empty(Queue* queue)
{
	return queue->count <= 0;
}

void clear (Queue* queue)
{
	free(queue->data);
	free(queue);
}

int main()
{
	Queue* q = init(double);
	double val;
	int op;
	while (scanf("%d", &op) != EOF)
	{
		switch (op)
		{
			case 1:
				scanf("%lf", &val);
				push(q, val);
				break;
			case 2:
				pop(q);
				break;
			case 3:
				printf("%lf\n", front(q, double));
				break;
			default:
				fprintf(stderr,"error input\n");
		}
	}

	return 0;
}


