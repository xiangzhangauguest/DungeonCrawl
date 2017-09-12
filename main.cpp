#include <iostream>
#include <string>

const int MapWidth      = 10;
const int MapHeight     = 7;

// These make our lives easier if we ever decide to change the symbols:
const char PlayerSymbol = 'G';
const char TrapSymbol   = 'T';
const char ExitSymbol   = 'X';
const char EmptySymbol  = '0';

enum Keys
{
    Right = 'd',
    Left  = 'a',
    Up    = 'w',
    Down  = 's',
    Quit  = 'q'
};

enum GameState
{
    HitTrap,
    FoundExit,
    KeepLooking,
    QuitGame
};

void print_map(const char map[MapWidth][MapHeight])
{
    for (int y = 0; y < MapHeight; ++y)
    {
        for (int x = 0; x < MapWidth; ++x)
        {
            std::cout << map[x][y];
        }
        std::cout << "\n";
    }
}

void clear_map(char map[MapWidth][MapHeight])
{
    for (int y = 0; y < MapHeight; ++y)
    {
        for (int x = 0; x < MapWidth; ++x)
        {
            map[x][y] = EmptySymbol;
        }
    }
}

void place_props(char map[MapWidth][MapHeight])
{
    // The initial player position (0,0):
    map[0][0] = PlayerSymbol;

    // Traps:
    map[4][1] = TrapSymbol;
    map[2][3] = TrapSymbol;
    map[1][4] = TrapSymbol;
    map[1][6] = TrapSymbol;

    // Exit is at the right end of the map.
    map[MapWidth - 1][MapHeight - 1] = ExitSymbol;
}

GameState move_player(char map[MapWidth][MapHeight],
                      int & currPlayerPosX, int & currPlayerPosY,
                      int desiredPlayerX,   int desiredPlayerY)
{
    // Clamp the new desired position to stay within the map bounds:
    if (desiredPlayerX < 0) { desiredPlayerX = 0; }
    if (desiredPlayerY < 0) { desiredPlayerY = 0; }
    if (desiredPlayerX >= MapWidth)  { desiredPlayerX = MapWidth  - 1; }
    if (desiredPlayerY >= MapHeight) { desiredPlayerY = MapHeight - 1; }

    GameState newState;

    // Check victory condition or if we hit a trap:
    if (map[desiredPlayerX][desiredPlayerY] == TrapSymbol)
    {
        std::cout << "You hit a trap an got decapitated! Better luck next time.\n";
        newState = HitTrap;
    }
    else if (map[desiredPlayerX][desiredPlayerY] == ExitSymbol)
    {
        std::cout << "You find the exit and live another day to tell the tales of your adventures!\n";
        newState = FoundExit;
    }
    else
    {
        newState = KeepLooking;
    }

    // Clear current position:
    map[currPlayerPosX][currPlayerPosY] = EmptySymbol;

    // Place the player symbol:
    map[desiredPlayerX][desiredPlayerY] = PlayerSymbol;

    // Return the new clamped position, avoiding the player from leaving the map.
    // Since we are using a reference to int, this change will be visible outside.
    currPlayerPosX = desiredPlayerX;
    currPlayerPosY = desiredPlayerY;
    return newState;
}

int main()
{
    int playerPosX = 0;
    int playerPosY = 0;
    GameState gameState = KeepLooking;
    char world_map[MapWidth][MapHeight];

    clear_map(world_map);
    place_props(world_map);
    print_map(world_map);

    while (gameState == KeepLooking)
    {
        char key;
        std::cin >> key;

        if (key == Right)
        {
            gameState = move_player(world_map, playerPosX, playerPosY, playerPosX + 1, playerPosY);
        }
        else if (key == Left)
        {
            gameState = move_player(world_map, playerPosX, playerPosY, playerPosX - 1, playerPosY);
        }
        else if (key == Up)
        {
            gameState = move_player(world_map, playerPosX, playerPosY, playerPosX, playerPosY - 1);
        }
        else if (key == Down)
        {
            gameState = move_player(world_map, playerPosX, playerPosY, playerPosX, playerPosY + 1);
        }
        else if (key == Quit)
        {
            gameState = QuitGame;
        }
        else
        {
            std::cout << "Invalid direction, use W,S,A,D to move up, down, left, right. Q to quit.\n";
        }

        print_map(world_map);
    }
}