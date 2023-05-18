
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <windows.h>

#define M_PI 3.14159265358979323846 

const int SCREEN_X = 100;
const int SCREEN_Y = 40;


float A, B, C;
float x, y, z, ooz;
int xp, yp;
const int triangleEdge = 40;
const int triangleHeight = (int)(1.73 * triangleEdge/2 );
const int Height = sqrt(6) * triangleEdge / 3;
int K2 = 60;
float K1 = 40;
int index;

float zBuffer[SCREEN_X*SCREEN_Y];
char buffer[SCREEN_X * SCREEN_Y];

int background = ' ';

float increment = 0.2;

bool isTriangle(float x, float y);

float rotateX(int i, int j, int k);
float rotateY(int i, int j, int k);
float rotateZ(int i, int j, int k);

void projectSurface(float X, float Y, float Z, int ch);

int main()
{
	A = B = C = 0;
	printf("\x1b[2J");
	
	float depth = -triangleEdge / sqrt(24);
	float edge1[3] = { -triangleEdge / 2, triangleHeight, 0 };
	float edge2[3] = { -triangleEdge, 0, 0 };
	float edge3[3] = { triangleEdge / 2, triangleHeight, 0 };


	while (1)
	{

		memset(buffer, background, SCREEN_X*SCREEN_Y);
		memset(zBuffer, 0, SCREEN_X * SCREEN_Y * 4);
		
		
		
		
		for (float i = -triangleEdge/2; i <= triangleEdge/2; i+=increment)
		{
			for (float j = -triangleHeight/2; j <=triangleHeight*2/3 ; j+=increment)
			{
				if (isTriangle(i, j))
				{
					projectSurface(i, j, depth, '#');

				}
			}
		}

		
		
		printf("\x1b[H");
		for (int k = 0; k < SCREEN_X* SCREEN_Y + 1; k++)
		{
			putchar(k % SCREEN_X ? buffer[k] : 10);
		}

		A += 0.05;
		B += 0.05;
		C += 0.01;
		Sleep(30);
		
	}

	
	return 0;
}

bool isTriangle(float x, float y)
{
	if (y <= sqrt(3) * (x - triangleEdge)/3 && y <= sqrt(3) * (-x + triangleEdge )/3)
		return true;
	else
		return false;
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
	
	x = rotateX(X, Y, Z);
	y = rotateY(X, Y, Z);
	z = rotateZ(X, Y, Z) + K2;

	
	ooz = 1 / z;

	xp = (int)(SCREEN_X / 2 + K1 * ooz * x * 2);
	yp = (int)(SCREEN_Y / 2 + K1 * ooz * y);

	index = xp + yp * SCREEN_X;
	if (index >= 0 && index < SCREEN_X * SCREEN_Y)
		if (ooz > zBuffer[index])
		{
			zBuffer[index] = ooz;
			buffer[index] = ch;
		}
}




