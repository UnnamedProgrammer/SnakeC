#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

// bool
#define true 1
#define false 0

#define WORLD_SIZE_X 25
#define WORLD_SIZE_Y 25

// Направление змейки
#define LEFT 'L'
#define RIGHT 'R'
#define UP 'U'
#define DOWN 'D'

struct Snake
{
    int x;
    int y;
    int segments;
    int speed;
    char head;

    char direction;
};

struct Snake snake;

char game_field[WORLD_SIZE_X][WORLD_SIZE_Y];

void init_game();
void game_draw();
void draw_snake(char game_field[][WORLD_SIZE_Y]);
void game_loop();

int main(void)
{
    setlocale(LC_ALL, "");
    WINDOW *w = initscr();
    cbreak();
    nodelay(w, TRUE);
    keypad(stdscr, true);
    curs_set(0);
    init_game();
    game_loop();
    return 0;
}

void init_game()
{
    snake.x = WORLD_SIZE_X / 2;
    snake.y = WORLD_SIZE_Y / 2;
    snake.head = 'O';
    snake.direction = UP;

    for (int y = 0; y <= WORLD_SIZE_Y; y++)
    {
        for (int x = 0; x <= WORLD_SIZE_X; x++)
        {
            if ((x == 0) || (y == WORLD_SIZE_Y))
            {
                game_field[x][y] = '#';
            }
            else if ((x > 0) && (x <= WORLD_SIZE_X) && (y == 0))
            {
                game_field[x][y] = '#';
            }
            else if ((x > 0) && (x <= WORLD_SIZE_X))
            {
                if (x == WORLD_SIZE_X)
                {
                    game_field[x][y] = '#';
                    continue;
                }
                game_field[x][y] = '.';
            }
        }
    }

    game_field[snake.x][snake.y] = 'O';
}

void game_draw()
{
    clear();
    for (int y = 0; y <= WORLD_SIZE_Y; y++)
    {
        for (int x = 0; x <= WORLD_SIZE_X; x++)
        {
            printw("%c", game_field[x][y]);
        }
        printw("\n");
    }
    draw_snake(game_field);
    refresh();
}

void draw_snake(char game_field[][WORLD_SIZE_Y])
{
    switch (snake.direction)
    {
    case UP:
        if (snake.y != 1)
        {
            game_field[snake.x][snake.y] = '.';
            snake.y--;
            game_field[snake.x][snake.y] = snake.head;
        }
        break;
    case DOWN:
        if (snake.y != 49)
        {
            game_field[snake.x][snake.y] = '.';
            snake.y++;
            game_field[snake.x][snake.y] = snake.head;
        }
        break;
    case LEFT:
        if (snake.x != 1)
        {
            game_field[snake.x][snake.y] = '.';
            snake.x--;
            game_field[snake.x][snake.y] = snake.head;
        }
        break;
    case RIGHT:
        if (snake.x != 49)
        {
            game_field[snake.x][snake.y] = '.';
            snake.x++;
            game_field[snake.x][snake.y] = snake.head;
        }
        break;
    }
    switch (getch())
    {
    case 'w':
        snake.direction = UP;
        break;
    case 's':
        snake.direction = DOWN;
        break;
    case 'a':
        snake.direction = LEFT;
        break;
    case 'd':
        snake.direction = RIGHT;
        break;
    }
}

void game_loop()
{
    while (true)
    {
        game_draw();
        sleep(1);
    }
}