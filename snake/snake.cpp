#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

const char BORDER = '#';
const char SNAKE = 'O';
const char APPLE = 'A';

const char LEFT = 'a';
const char RIGHT = 'd';
const char UP = 'w';
const char DOWN = 's';
const char OUT = 'x';

const int LEFT_DIRECTION = 3;
const int RIGHT_DIRECTION = 1;
const int UP_DIRECTION = 0;
const int DOWN_DIRECTION = 2;

const string FINAL_TABLE = "Game Over";

const int WIDTH = 20;
const int HEIGHT = 10;
const int DELAY = 500;

int appleX, appleY;

int snakeX, snakeY;
int snakeDir;

vector<pair<int, int>> snakeBody;

bool gameOver;

void Setup()
{
    srand(time(0));

    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    snakeDir = 0;

    appleX = rand() % WIDTH;
    appleY = rand() % HEIGHT;

    gameOver = false;
}

void Draw()
{
    system("cls");

    cout << string(WIDTH + 2, BORDER) << endl;

    vector<vector<char>> gameField(HEIGHT, vector<char>(WIDTH, ' '));

    gameField[snakeY][snakeX] = SNAKE;
    gameField[appleY][appleX] = APPLE;
    for (pair<int, int> bodyPart : snakeBody)
        gameField[bodyPart.second][bodyPart.first] = SNAKE;

    for (int y = 0; y < HEIGHT; y++)
    {
        cout << BORDER;
        for (int x = 0; x < WIDTH; x++)
        {
            cout << gameField[y][x];
        }
        cout << BORDER << endl;
    }
    cout << string(WIDTH + 2, BORDER) << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case LEFT:
            snakeDir = LEFT_DIRECTION;
            snakeX--;
            break;
        case RIGHT:
            snakeDir = RIGHT_DIRECTION;
            snakeX++;
            break;
        case UP:
            snakeDir = UP_DIRECTION;
            snakeY--;
            break;
        case DOWN:
            snakeDir = DOWN_DIRECTION;
            snakeY++;
            break;
        case OUT:
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    switch (snakeDir)
    {
    case UP_DIRECTION:
        snakeY--;
        break;
    case RIGHT_DIRECTION:
        snakeX++;
        break;
    case DOWN_DIRECTION:
        snakeY++;
        break;
    case LEFT_DIRECTION:
        snakeX--;
        break;
    }

    if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT)
        gameOver = true;

    if (snakeX == appleX && snakeY == appleY)
    {
        snakeBody.push_back(make_pair(snakeX, snakeY));
        appleX = rand() % WIDTH;
        appleY = rand() % HEIGHT;
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
    Sleep(DELAY);
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
    cout << FINAL_TABLE << endl;
    return 0;
}
