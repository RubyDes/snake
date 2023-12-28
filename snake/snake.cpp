#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

const char Border = '#';
const char Snake = 'O';
const char Apple = 'A';
const char Left = 'a';
const char Righ = 'd';
const char Up = 'w';
const char Dpwn = 's';
const char Out = 'x';

const string FinalTable = "Game Over";

const int Width = 20;
const int Height = 10;

int appleX, appleY;

int snakeX, snakeY;
int snakeDir;

vector<pair<int, int>> snakeBody;

bool gameOver;

void Setup()
{
    srand(time(0));

    snakeX = Width / 2;
    snakeY = Height / 2;
    snakeDir = 0;

    appleX = rand() % Width;
    appleY = rand() % Height;

    gameOver = false;
}

void Draw()
{
    system("cls");

    cout << string(Width + 2, Border) << endl;

    vector<vector<char>> gameField(Height, vector<char>(Width, ' '));

    gameField[snakeY][snakeX] = Snake;
    gameField[appleY][appleX] = Apple;
    for (pair<int, int> bodyPart : snakeBody)
        gameField[bodyPart.second][bodyPart.first] = Snake;

    for (int y = 0; y < Height; y++)
    {
        cout << Border;
        for (int x = 0; x < Width; x++)
        {
            cout << gameField[y][x];
        }
        cout << Border << endl;
    }
    cout << string(Width + 2, Border) << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case Left:
            snakeDir = 3;
            snakeX--;
            break;
        case Righ:
            snakeDir = 1;
            snakeX++;
            break;
        case Up:
            snakeDir = 0;
            snakeY--;
            break;
        case Dpwn:
            snakeDir = 2;
            snakeY++;
            break;
        case Out:
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    switch (snakeDir)
    {
    case 0:
        snakeY--;
        break;
    case 1:
        snakeX++;
        break;
    case 2:
        snakeY++;
        break;
    case 3:
        snakeX--;
        break;
    }

    if (snakeX < 0 || snakeX >= Width || snakeY < 0 || snakeY >= Height)
        gameOver = true;

    if (snakeX == appleX && snakeY == appleY)
    {
        snakeBody.push_back(make_pair(snakeX, snakeY));
        appleX = rand() % Width;
        appleY = rand() % Height;
    }
    else
    {
        if (!snakeBody.empty())
            snakeBody.pop_back();
    }

    for (pair<int, int> bodyPart : snakeBody)
    {
        if (bodyPart.first == snakeX && bodyPart.second == snakeY)
            gameOver = true;
    }
    Sleep(500);
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    cout << FinalTable << endl;
    return 0;
}