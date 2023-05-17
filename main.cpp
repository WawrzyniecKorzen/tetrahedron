
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <windows.h>

const int SIZE = 60;


float A, B, C;
float x, y, z, ooz;
int xp, yp;
float triangleSide = 10;
int K2 = 60;
float K1 = 40;
int index;

float zBuffer[SIZE*SIZE];
char buffer[SIZE*SIZE];

int background = ' ';

float increment = 0.6;

float rotateX(int i, int j, int k);
float rotateY(int i, int j, int k);
float rotateZ(int i, int j, int k);

void projectSurface(float X, float Y, float Z, int ch);

int main()
{
	A = B = C = 0;
	printf("\x1b[2J");

	while (1)
	{
		memset(buffer, background, SIZE*SIZE);
		memset(zBuffer, 0, SIZE * SIZE * 4);

		//for for - to cast a triangle and call project Surface

		printf("\x1b[H");
		for (int k = 0; k < SIZE * SIZE + 1; k++)
		{
			putchar(k % SIZE ? buffer[k] : 10);
		}

		A += 0.05;
		B += 0.05;
		C += 0.01;
		Sleep(10);
	}
	return 0;
}

float rotateX(int i, int j, int k)
{

	return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float rotateY(int i, int j, int k)
{
	return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
		j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
		i * cos(B) * sin(C);
}

float rotateZ(int i, int j, int k)
{
	return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void projectSurface(float X, float Y, float Z, int ch)
{
	//calculate x, y, z (+ distance to screen)


	//projection on screen
	ooz = 1 / z;

	xp = (int)(SIZE / 2 + K1 * ooz * x * 2);
	yp = (int)(SIZE / 2 + K1 * ooz * y);

	index = xp + yp * SIZE;
	if (index >= 0 && index < SIZE * SIZE)
		if (ooz > zBuffer[index])
		{
			zBuffer[index] = ooz;
			buffer[index] = ch;
		}
}


