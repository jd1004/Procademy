#pragma once

#define N 5

typedef struct
{
	int Time;
}UNIT;

UNIT Queue[N];
int Front;
int Rear;
bool Enqueue(UNIT unit);
bool Dequeue(UNIT*);
bool Peek(UNIT*, int Pos);

bool Enqueue(UNIT unit)
{
	if (Front == (Rear + 1) % N)
	{
		return false;
	}

	Rear = (Rear + 1) % N;
	Queue[Rear] = unit;
	return true;
}

bool Dequeue(UNIT* unit)
{
	if (Front == Rear)
	{
		return false;
	}
	Front = (Front + 1) % N;
	return true;
}

bool Peek(UNIT* unit, int Pos)
{
	if (Front == Rear)
	{
		return false;
	}

	return true;
}