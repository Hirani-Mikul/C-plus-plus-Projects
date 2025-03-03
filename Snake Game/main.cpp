#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

bool gameOver;

int x, y, fruitX, fruitY, score;
const int width = 20;
const int height = 20;

enum eDirection
{
  STOP = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN
};
eDirection dir;

void Start()
{
  gameOver = false;
  dir = STOP;

  x = width / 2;
  y = height / 2;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
}
void draw()
{
  system("cls");
  for (int i = 0; i < width + 2; i++)
    cout << "#";

  cout << endl;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (j == 0)
        cout << "#";
      if (i == y && j == x)
        cout << "O";
      else if (i == fruitY && j == fruitX)
        cout << "F";
      else
        cout
            << " ";

      if (j == width - 1)
        cout << "#";
    }
    cout << endl;
  }

  for (int i = 0; i < width + 2; i++)
    cout << "#";
  cout << endl;

  cout << "Score: " << score << endl;
}
void logic()
{

  if (x > width)
    x = 0;
  else if (x < 0)
    x = width;
  if (y > height)
    y = 0;
  else if (y < 0)
    y = height;

  switch (dir)
  {
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;

  default:
    break;
  }
  if (x == fruitX && y == fruitY)
  {
    score += 10;
    fruitX = rand() % width;
    fruitY = rand() % height;
  }
}
void input()
{
  if (_kbhit())
  {
    switch (_getch())
    {
    case 'a':
      dir = LEFT;
      break;
    case 'd':
      dir = RIGHT;
      break;
    case 'w':
      dir = UP;
      break;
    case 's':
      dir = DOWN;
      break;
    case 'x':
      gameOver = true;
      break;
    default:
      break;
    }
  }
}

int main()
{

  Start();

  while (!gameOver)
  {
    draw();
    input();
    logic();
  }

  Sleep(10);
  return 0;
}