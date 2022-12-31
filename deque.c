#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "includes/Entity.h"
#include "includes/Deque.h"
#include "includes/Snake.h"



Deque* deque_init()
{
	Deque *initialized = (Deque*) malloc(sizeof(Deque));

	if (initialized == NULL)
	{
		system("pause > Problem with allocating memory for Deque.Please press any key to exit...");
		exit(1);
	}
	initialized->front = NULL;
	initialized->rear = NULL;
	initialized->length = 0;

	return initialized;
}

void deque_push(Deque *q, Vector *coords)
{
	Snake_Node* snake = (Snake_Node*) malloc(sizeof(Snake_Node));
    
	if (snake == NULL)
	{
		system("pause > Problem with allocating memory for Node.Please press any key to exit...");
		exit(1);
	}

	snake->coords = coords;
	snake->next = NULL;

	if (q->front == NULL && q->rear == NULL)
	{
		q->front = q->rear = snake;
		q->length++;
		return;
	}

	q->rear->next = snake;
	q->rear = snake;
	q->length++;
}


Vector *deque_front (Deque *q)
{
	if (q->front != NULL)
		return q->front->coords;
}

Vector *deque_back(Deque *q)
{
	if (q->rear != NULL)
		return q->rear->coords;
}