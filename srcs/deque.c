#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "Entity.h"
#include "Deque.h"
#include "Snake.h"



Deque* deque_init()
{
	Deque *initialized = (Deque*) malloc(sizeof(Deque));

	if (initialized == NULL)
		system("pause > Problem with allocating memory for Deque.Please press any key to exit...");

	initialized->front = NULL;
	initialized->rear = NULL;
	initialized->length = 0;

	return initialized;
}

void deque_push(Deque *q, Vector *coords)
{
	Snake_Node* snake = (Snake_Node*) malloc(sizeof(Snake_Node));

	if (snake == NULL)
		system("pause > Problem with allocating memory for Node.Please press any key to exit...");

	snake->coords = coords;
	snake->next = NULL;

	if (q->front == NULL && q->rear == NULL)
	{
		q->front = q->rear = snake;
		// q->length++;
		return;
	}

	q->rear->next = snake;
	q->rear = snake;
	q->length++;
}

Vector *deque_pop(Deque *q)
{
	Snake_Node* element = q->front;
	if (q->front == NULL) //Queue is empty return
		return;

	if (q->front == q->rear)
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;

	Vector *returnedData = element->coords;
	q->length;
	free(element);
	return returnedData;
}



Vector *deque_front (Deque *q)
{
	if (q->front != NULL)
		return q->front->coords;
	return NULL;
}

Vector *deque_back(Deque *q)
{
	if (q->rear != NULL)
		return q->rear->coords;
	return NULL;
}
