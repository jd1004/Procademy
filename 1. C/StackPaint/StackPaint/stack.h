#pragma once

#define STACK_MAX 30

typedef struct
{
	int x[STACK_MAX];
	int y[STACK_MAX];
	int top;

}Stack;

void Init(Stack* stack)
{
	stack->top = -1;
}

bool Push(Stack* stack, int x, int y)
{
	if (stack->top + 1 >= STACK_MAX)
		return false;

	stack->top += 1;

	stack->x[stack->top] = x;
	stack->y[stack->top] = y;

	return true;
}

bool Pop(Stack* stack, int* x, int* y)
{
	if (stack->top < 0)
		return false;

	*x = stack->x[stack->top];
	*y = stack->y[stack->top];

	stack->top -= 1;

	return true;
}