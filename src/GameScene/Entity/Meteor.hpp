// Meteor.hpp
#pragma once
#include "gameobject.hpp"
#include "../World/Constants.hpp"
#include "../World/Utils.hpp"
#include "../Camera2D.hpp"
#include <Engine.hpp>
#include <random>
#include "Collider.h"
#include "BulletManager.h"

class Meteor : public GameObject
{
private:
    float x, y; // Центр метеорита
    float width, height;
    float speed;
    float rotation;
    float rotationSpeed;
    Math::vec2 velocity;
    HitBox hitBox;
    bool isDestroyed;

    Texture *texture;

    // Генератор случайных чисел
    static std::random_device rd;
    static std::mt19937 gen;

    void updateCollisionBoard(GameState &state)
    {
        // Очищаем старую позицию
        int oldCellX = static_cast<int>(hitBox.rec.x / GameConstants::CELL_SIZE);
        int oldCellY = static_cast<int>(hitBox.rec.y / GameConstants::CELL_SIZE);
        if (Utils::isPointInMap(oldCellX, oldCellY))
        {
            state.collisionBoard[oldCellX][oldCellY] = false;
        }

        // Обновляем новую позицию
        int cellX = static_cast<int>(x / GameConstants::CELL_SIZE);
        int cellY = static_cast<int>(y / GameConstants::CELL_SIZE);
        if (Utils::isPointInMap(cellX, cellY))
        {
            state.collisionBoard[cellX][cellY] = true;
        }
    }

public:
    Meteor(float x, float y)
        : GameObject("Meteor"),
          x(x), y(y),
          width(GameConstants::CELL_SIZE * 2),
          height(GameConstants::CELL_SIZE * 2),
          speed(5.0f),
          rotation(0.0f),
          isDestroyed(false) // Инициализируем флаг
    {
        // Инициализация генератора случайных чисел
        static bool initialized = false;
        if (!initialized)
        {
            gen.seed(rd());
            initialized = true;
        }

        // Случайная скорость вращения от -2 до 2 градусов за кадр
        std::uniform_real_distribution<float> distRot(-2.0f, 2.0f);
        rotationSpeed = distRot(gen);

        // Случайное начальное направление
        std::uniform_real_distribution<float> distVelX(-1.0f, 1.0f);
        std::uniform_real_distribution<float> distVelY(0.5f, 2.0f);
        velocity = {distVelX(gen), distVelY(gen)};

        hitBox = (HitBox){(Rect){x - width / 2, y - height / 2, width, height}, 100, rotation, TEAM_ENEMY};
        hitBox.rec.x = x;
        hitBox.rec.y = y;
        bulletManager.AddHitBox(getHitBox());

        int texture_index = Random::Int(0, 7);
        std::string randomSoundName = "meteor:" + std::to_string(texture_index);
        texture = ResourceManager::GetTexture(randomSoundName);
    }
    
    ~Meteor()
    {
        bulletManager.RemoveHitBox(&hitBox);
    }

    void update() override
    {
        if (isDestroyed || hitBox.health <= 0)
        {
            destroy();
            return;
        }

        // Обновляем позицию (центр метеорита)
        x += velocity.x * Time::getDelta() * speed;
        y += velocity.y * Time::getDelta() * speed;

        // Обновляем вращение
        rotation += rotationSpeed;
        if (rotation > 360)
            rotation -= 360;
        if (rotation < 0)
            rotation += 360;

        // Обновляем hitbox (левый верхний угол)
        hitBox.rec.x = x;
        hitBox.rec.y = y;
        hitBox.rotation = rotation;

        // Проверка выхода за границы мира
        if (y - height / 2 > GameConstants::WORLD_HEIGHT)
        {
            hitBox.health = 0; // Уничтожаем метеорит, если он упал за пределы мира
        }
    }

    void destroy()
    {
        if (isDestroyed) return;
        isDestroyed = true;
        bulletManager.RemoveHitBox(getHitBox());
    }

    void updateWithState(GameState &state)
    {
        update();
        updateCollisionBoard(state);
    }

    void draw() override
    {
        if (hitBox.health <= 0)
            return;

        Math::vec4 color = {150, 75, 0, 255};

        Draw2D::Sprite(

            x - width / 2, y - height / 2, width, height,
            
            texture,
            Color::white, rotation);

        bool debug = false;
        if (debug)
        {
            DrawCollieder(main_camera.GetViewMatrix(),
                          (Rect){
                              hitBox.rec.x,
                              hitBox.rec.y,
                              hitBox.rec.width,
                              hitBox.rec.height},
                          Utils::radians(hitBox.rotation));
        }
    }

    RectangleF getRect() const
    {
        return {x - width / 2, y - height / 2, x + width / 2 - 1, y + height / 2 - 1};
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getHealth() const { return hitBox.health; }
    float getRotation() const { return rotation; }
    void takeDamage(float damage) { hitBox.health -= damage; }
    void setVelocity(Math::vec2 newVelocity) { velocity = newVelocity; }
    HitBox *getHitBox() { return &hitBox; }
    bool isAlive() const { return !isDestroyed && hitBox.health > 0 && y - height / 2 <= GameConstants::WORLD_HEIGHT; }
};

// Инициализация статических членов класса
std::random_device Meteor::rd;
std::mt19937 Meteor::gen;