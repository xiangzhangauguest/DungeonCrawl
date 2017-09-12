#include <iostream>
#include <vector>

using namespace std;

const int G = 5;
const int ROAD = 0;
const int T = 1;
const int X = 2;

enum Directions
{
    Left = 'a',
    Right = 'd',
    Up = 'w',
    Down = 's',
    Quit = 'q'
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
        return {this->ROW, this->COL};
    }

    void show()
    {
        for (const auto& row : this->map) {
            for (const auto &element : row) {
                if (element == G) cout << "G ";
                if (element == T) cout << "T ";
                if (element == X) cout << "X ";
                if (element == ROAD) cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void update(unsigned pre_x, unsigned pre_y, unsigned x, unsigned y)
    {
        this->map[pre_x][pre_y] = ROAD;
        this->map[x][y] = G;
    }

    int check(unsigned x, unsigned y)
    {
        return this->map[x][y];
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
        unsigned pre_x = this->x, pre_y = this->y;

        auto shape = map.getShape();
        if (direction == Left && y > 0) this->y--;
        if (direction == Right && y < shape.second - 1) this->y++;
        if (direction == Up && x > 0) this->x--;
        if (direction == Down && x < shape.first - 1) this->x++;

        int status = map.check(x, y);
        if (status == ROAD)
            map.update(pre_x, pre_y, x, y);

        return status;
    }
};

int main()
{
    Player player;
    Map map;
    char direction;

    map.show();
    cout << "Welcome to Dungeon Crawl.\nInput a s w d to go to a direction.\n";
    while (cin >> direction) {
        if (direction == Quit) {
            cout << "Quit the game.\n";
            break;
        }
        int status = player.move(map, direction);
        map.show();
        if (status == T) {
            cout << "You are trapped.\nGame Over!\n";
            break;
        }
        if (status == X) {
            cout << "You find the treasure!\nCongratulations!\n";
            break;
        }
    }

    return 0;
}