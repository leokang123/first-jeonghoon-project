#include <iostream>
#include <cmath>
#include <unistd.h>
#include <cstring>

using namespace std;

float A,B; // A만 가지고 각도를 변화를 주면 평면에서의 평면 rotation이 되고  A,B두 각도 모두 사용하면 공간에서의 평면 rotation이된다

float Squarewidth = 20;
int width = 160;
int height = 44;
float zBuffer [160*44];
char buffer[160*44];
int backgroundASCIICode = '.';
int distanceFromCam = 50;
float K1 = 0.5;

float incrementSpeed = 1;

float x,y;
float xp,yp;
int idx;

float calculateX(int i,int j)
{
    return i * cos(A) - j * sin(A);
}

float calculateY(int i,int j)
{
    return i * sin(B) + j * cos(B);
}

void calculateForSurface(float squareX,float squareY,int ch)
{
  x = calculateX(squareX,squareY);
  y = calculateY(squareX,squareY);

  xp = (int)(width / 2 + K1 * x * 1.8);
  yp = (int)(height / 2  + K1  *  y );

  idx = xp + yp * width;
  if (idx >= 0 && idx < width*height ) {
    buffer[idx] = ch;
  }
}

int main(void)
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout<<"\x1b[2j";
  while(1)
  {
    memset(buffer,backgroundASCIICode,width*height);
    memset(zBuffer,0,width*height);
    for(float squareX = -Squarewidth;squareX<Squarewidth;squareX += incrementSpeed)
    {
      for(float squareY = -Squarewidth;squareY<Squarewidth;squareY += incrementSpeed)
      {
        calculateForSurface(squareX,squareY,'%');
        
      }
    }
    cout<<"\x1b[H";
    for(int k = 0;k < width*height;k++)
    {
      putchar(k%width ? buffer[k] : 10);
    }
    A += 0.005;  // 
    B += 0.005;
    usleep(1000);
  }
  return 0;
}