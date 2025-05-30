// -----[ Constants.hpp ]----- //
#pragma once

class GameObject;

enum BulletTeam
{
    TEAM_ENEMY,
    TEAM_FRIENDLY
};
typedef struct HitBox
{
    Rect rec;
    int health;
    float rotation;
    BulletTeam team;
    GameObject* owner;
} HitBox;

typedef struct Bullet
{
    Rect rec;
    float angle;
    int speed;
    BulletTeam team;
    float damage;  // Добавляем параметр урона
} Bullet;

namespace GameConstants
{
    // World dimensions
    const int WORLD_WIDTH = 8400;
    const int WORLD_HEIGHT = 2400;
    const int CELL_SIZE = 40;
    const int GRID_WIDTH = WORLD_WIDTH / CELL_SIZE;
    const int GRID_HEIGHT = WORLD_HEIGHT / CELL_SIZE;

    // Cell types
    enum CellType
    {
        SPACE = 0,
        METEOR = 7    
    };
}

class Player;

struct GameState
{
    bool collisionBoard[GameConstants::GRID_WIDTH][GameConstants::GRID_HEIGHT] = {false};
    
    Player* player;
    
};

GameState state;