

#include <cmath>
#include <stdio.h>
#include <windows.h>



const int SCREEN_X = 100;
const int SCREEN_Y = 40;


float A, B, C;
float x, y, z, ooz;
int xp, yp;
const int triangleEdge = 40;
float  triangleHeight = (sqrt(3) * triangleEdge / 2.0);
float K2 = 60;
float K1 = 40;
int index;

float zBuffer[SCREEN_X * SCREEN_Y];
char buffer[SCREEN_X * SCREEN_Y];

int background = ' ';

float increment = 0.2;

bool isTriangle(float x, float y);

float rotateX(float i, float j, float k);
float rotateY(float i, float j, float k);
float rotateZ(float i, float j, float k);

void projectSurface(float X, float Y, float Z, int ch);
void firstFace(float& X, float& Y, float& Z);
void secondFace(float& X, float& Y, float& Z);
void thirdFace(float& X, float& Y, float& Z);


int main()
{
	A = B = C = 0;
	printf("\x1b[2J");

	float depth = -triangleEdge / sqrt(24);



	while (1)
	{

		memset(buffer, background, SCREEN_X * SCREEN_Y);
		memset(zBuffer, 0, SCREEN_X * SCREEN_Y * 4);


		float iX, jY, kZ;


		for (float i = -triangleEdge / 2.0; i <= triangleEdge / 2.0; i += increment)
		{
			for (float j = -triangleHeight / 3.0; j <= triangleHeight * 2.0 / 3.0; j += increment)
			{
				if (isTriangle(i, j))
				{
					projectSurface(i, j, depth, '#');

					iX = i;
					jY = j;
					kZ = depth;
					firstFace(iX, jY, kZ);
					projectSurface(iX, jY, kZ, ':');

					iX = i;
					jY = j;
					kZ = depth;
					secondFace(iX, jY, kZ);
					projectSurface(iX, jY, kZ, '~');

					iX = i;
					jY = j;
					kZ = depth;
					thirdFace(iX, jY, kZ);
					projectSurface(iX, jY, kZ, ';');

				}
			}


		}

		printf("\x1b[H");
		for (int k = 0; k < SCREEN_X * SCREEN_Y + 1; k++)
		{
			putchar(k % SCREEN_X ? buffer[k] : 10);
		}

		A += 0.1;
		B += 0.1;
		//C += 0.1;
		Sleep(30);

	}




	return 0;
}

bool isTriangle(float x, float y)
{
	if (y <= sqrt(3) * (x + triangleEdge / 3.0) && y <= sqrt(3) * (-x + triangleEdge / 3.0))
		return true;
	else
		return false;
}

float rotateX(float i, float j, float k)
{

	return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float rotateY(float i, float j, float k)
{
	return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
		j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
		i * cos(B) * sin(C);
}

float rotateZ(float i, float j, float k)
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

void firstFace(float& X, float& Y, float& Z)
{
	float tempX;
	float tempY;
	float tempZ;

	tempX = X * 0.5 - Y * 1 / (2 * sqrt(3)) + Z * sqrt(2.0 / 3.0) + triangleEdge / 3.0;
	tempY = -X * 1.0 / (2 * sqrt(3)) + Y * 5.0 / 6 + Z * sqrt(2) / 3.0 + triangleEdge / (3.0 * sqrt(3));
	tempZ = -X * sqrt(2.0 / 3.0) - Y * sqrt(2) / 3.0 + Z / 3.0 + triangleEdge / (3.0 * sqrt(6));
	X = tempX;
	Y = tempY;
	Z = tempZ;
}

void secondFace(float& X, float& Y, float& Z)
{
	float tempX;
	float tempY;
	float tempZ;

	tempX = X * 0.5 + Y * 1 / (2 * sqrt(3)) - Z * sqrt(2.0 / 3.0) - triangleEdge / 3.0;
	tempY = X * 1.0 / (2 * sqrt(3)) + Y * 5.0 / 6 + Z * sqrt(2) / 3.0 + triangleEdge / (3.0 * sqrt(3));
	tempZ = X * sqrt(2.0 / 3.0) - Y * sqrt(2) / 3.0 + Z / 3.0 + triangleEdge / (3.0 * sqrt(6));
	X = tempX;
	Y = tempY;
	Z = tempZ;
}

void thirdFace(float& X, float& Y, float& Z)
{

	float tempY;
	float tempZ;
	tempY = Y * 1.0 / 3.0 - Z * (2 * sqrt(2) / 3.0) - 2 * triangleEdge / (3 * sqrt(3));
	tempZ = Y * (2 * sqrt(2) / 3.0) + Z / 3.0 + triangleEdge / (3.0 * sqrt(6));
	Y = tempY;
	Z = tempZ;
}











