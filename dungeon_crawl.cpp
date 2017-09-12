#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

const int G = 5;
const int ROAD = 0;
const int T = 1;
const int X = 2;
const int E = 3;
const char QUIT = 'q';

enum Directions
{
    Left = 'a',
    Right = 'd',
    Up = 'w',
    Down = 's'
};

class Map
{
private:
    const unsigned COL =  12;
    const unsigned ROW =  8;
    vector<vector<int> > map = {{5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}};

public:
    const pair<unsigned, unsigned> getShape()
    {
        return {ROW, COL};
    }

    void show()
    {
        for (const auto& row : map) {
            for (const auto &element : row) {
                if (element == G) cout << "G ";
                if (element == T) cout << "T ";
                if (element == X) cout << "X ";
                if (element == E) cout << "E ";
                if (element == ROAD) cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void update(unsigned pre_x, unsigned pre_y, unsigned x, unsigned y, int who)
    {
        map[pre_x][pre_y] = ROAD;
        map[x][y] = who;
    }

    int check(unsigned x, unsigned y)
    {
        return map[x][y];
    }
};

class Player
{
private:
    unsigned x = 0;
    unsigned y = 0;

public:
    int move(Map& map, char direction)
    {
        unsigned pre_x = x, pre_y = y;

        auto shape = map.getShape();
        if (direction == Left && y > 0) y--;
        if (direction == Right && y < shape.second - 1) y++;
        if (direction == Up && x > 0) x--;
        if (direction == Down && x < shape.first - 1) x++;

        int status = map.check(x, y);
        if (status == ROAD)
            map.update(pre_x, pre_y, x, y, G);

        return status;
    }
};

class Enemy
{
private:
    unsigned x;
    unsigned y;

public:
    Enemy()
    {
        x = 1;
        y = 0;
    }
    Enemy(Map& map)
    {
        auto shape = map.getShape();
        x = shape.second / 2;
        y = shape.first / 2;
        map.update(x, y, x, y, E);
    }

    void move(Map& map)
    {
        unsigned pre_x = x, pre_y = y;
        do {
            x = pre_x;
            y = pre_y;
            int direction = rand() % 4;

            auto shape = map.getShape();
            if (direction == 0 && y > 0) y--;
            if (direction == 1 && y < shape.second - 1) y++;
            if (direction == 2 && x > 0) x--;
            if (direction == 3 && x < shape.first - 1) x++;
        }
        while (map.check(x, y) != ROAD && map.check(x, y) != G);

        map.update(pre_x, pre_y, x, y, E);
    }
};

int main()
{
    Map map;
    Player player;
    Enemy enemy(map);
    char direction;

    map.show();
    cout << "Welcome to Dungeon Crawl.\nInput a s w d to go to a direction.\n";
    while (cin >> direction) {
        enemy.move(map);
        if (direction == QUIT) {
            cout << "Quit the game.\n";
            break;
        }
        int status = player.move(map, direction);
        map.show();
        if (status == T) {
            cout << "You are trapped.\nGame Over!\n";
            break;
        }
        if (status == E) {
            cout << "You meet the enemy!\nGame Over!\n";
            break;
        }
        if (status == X) {
            cout << "You find the treasure!\nCongratulations!\n";
            break;
        }
    }

    return 0;
}