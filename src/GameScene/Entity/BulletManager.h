// -----[ BulletManager.h ]----- //
// BulletManager.h
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>

#include <Engine.hpp>
#include "Collider.h"
#include "../Camera2D.hpp"

#include "../World/Utils.hpp"
#include "../World/Constants.hpp"

#define MAXBULLET 100

class BulletManager
{
private:
    std::vector<Bullet> bullets;
    std::vector<HitBox *> hitBoxes;

    bool CheckMapCollision(float x, float y)
    {
        int cellX = static_cast<int>(x / GameConstants::CELL_SIZE);
        int cellY = static_cast<int>(y / GameConstants::CELL_SIZE);

        if (!Utils::isPointInMap(cellX, cellY))
            return false;

        return state.collisionBoard[cellX][cellY];
    }

public:
    void AddHitBox(HitBox *hitBox) // Remove the const qualifier
    {
        if (hitBox != nullptr)
        {
            hitBoxes.push_back(hitBox);
        }
    }

    void RemoveHitBox(HitBox *hitBox)
    {
        if (hitBox == nullptr) return;
        hitBoxes.erase(std::remove(hitBoxes.begin(), hitBoxes.end(), hitBox), hitBoxes.end());
    }

    void ClearHitBoxes()
    {
        hitBoxes.clear();
    }

    void Update(double time)
    {
        for (auto it = bullets.begin(); it != bullets.end();)
        {
            float newX = it->rec.x + (float)cos(Utils::radians(it->angle)) * it->speed;
            float newY = it->rec.y + (float)sin(Utils::radians(it->angle)) * it->speed;

            bool collided = false;

            // 2. Проверка столкновений с игроком/хитбоксами
            if (!collided)
            {
                for (auto &hitBox : hitBoxes)
                {
                    if (hitBox &&
                        (it->team != hitBox->team) &&
                        CheckCollision(it->rec, hitBox->rec, it->angle, hitBox->rotation))
                    {
                        // Вместо прямого изменения здоровья вызываем метод объекта
                        if (hitBox->owner)
                        {
                            hitBox->owner->takeDamage(it->damage);
                        }
                        else
                        {
                            hitBox->health -= it->damage; // fallback для объектов без owner
                        }
                        collided = true;
                        break;
                    }
                }
            }

            // 3. Проверка столкновений с картой (последний приоритет)
            if (!collided)
            {
                bool collidedWithMap = false;
                float step = 0.5f;
                float dx = (newX - it->rec.x) * step;
                float dy = (newY - it->rec.y) * step;

                for (float t = 0; t <= 1.0f; t += step)
                {
                    float checkX = it->rec.x + dx * t;
                    float checkY = it->rec.y + dy * t;

                    if (CheckMapCollision(checkX, checkY) ||
                        CheckMapCollision(checkX + it->rec.width, checkY) ||
                        CheckMapCollision(checkX, checkY + it->rec.height) ||
                        CheckMapCollision(checkX + it->rec.width, checkY + it->rec.height))
                    {
                        collidedWithMap = true;
                        break;
                    }
                }
                collided = collidedWithMap;
            }

            // Обновление позиции пули, если не было столкновений
            if (!collided)
            {
                it->rec.x = newX;
                it->rec.y = newY;

                // Проверка выхода за границы мира
                if (it->rec.x < -50 || it->rec.x > GameConstants::WORLD_WIDTH + 50 ||
                    it->rec.y < -50 || it->rec.y > GameConstants::WORLD_HEIGHT + 50)
                {
                    collided = true;
                }
            }

            // Удаление пули при столкновении или выходе за границы
            if (collided)
            {
                it = bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void Draw()
    {
        for (auto &bullet : bullets)
        {
            Math::vec4 bulletColor = (bullet.team == TEAM_FRIENDLY) ? Color::blue : Color::red;
            Draw2D::Sprite(
                           bullet.rec.x, bullet.rec.y, bullet.rec.width, bullet.rec.height,
                           
                           ResourceManager::GetTexture("bullet"),
                           bulletColor, bullet.angle);
        }

        bool debug = false;
        if (debug)
        {
            for (auto &hitBox : hitBoxes) // Исправлено имя итератора
            {
                if (hitBox) // Добавлена проверка на nullptr
                {
                    DrawCollieder(main_camera.GetViewMatrix(),
                                  (Rect){
                                      hitBox->rec.x,
                                      hitBox->rec.y,
                                      hitBox->rec.width,
                                      hitBox->rec.height},
                                  Utils::radians(hitBox->rotation));
                }
            }
        }
    }

    void Shoot(Math::vec2 worldPosition, float rotation, int speed, float damage, BulletTeam team = TEAM_FRIENDLY)
    {
        if (bullets.size() >= MAXBULLET)
            return;

        Bullet bullet = {0};
        bullet.angle = rotation;
        bullet.rec = (Rect){worldPosition.x, worldPosition.y, 20, 20};
        bullet.speed = speed;
        bullet.team = team;
        bullet.damage = damage; // Устанавливаем урон
        bullets.push_back(bullet);
    }

    void Clear()
    {
        bullets.clear();
    }
};

BulletManager bulletManager;

#endif