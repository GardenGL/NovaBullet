// -----[ Mob.hpp ]----- //
#pragma once

#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <Engine.hpp>
#include "../World/Utils.hpp"
#include "../World/Constants.hpp"
#include "gameobject.hpp"
#include "BulletManager.h"
#include "../Camera2D.hpp"

using namespace Math;
using namespace GameConstants;

class Mob : public GameObject
{
private:
    float x, y, width, height;
    HitBox hitBox;
    float rotation;
    float speed;
    float searchRadius;
    float shootRadius;

    // Shooting variables
    float fireRate;
    float nextFireTime;
    float bulletSpeed;

    Texture *texture;
    bool isDestroyed;

public:
    Mob(float x, float y) : GameObject("Mob"), x(x), y(y), isDestroyed(false)
    {
        width = CELL_SIZE * 2;
        height = CELL_SIZE * 2;
        hitBox = (HitBox){(Rect){x + width / 2, y + height / 2, width, height}, 100, 0.0f, TEAM_ENEMY};
        rotation = 0.0f;
        speed = 2.0f;
        searchRadius = CELL_SIZE * 30;
        shootRadius = CELL_SIZE * 10;
        fireRate = 1.0f;
        nextFireTime = 0.0f;
        bulletSpeed = 5.0f;

        bulletManager.AddHitBox(getHitBox());

        int texture_index = Random::Int(0, 4);
        std::string randomSoundName = "enemy:" + std::to_string(texture_index);
        texture = ResourceManager::GetTexture(randomSoundName);
    }

    ~Mob()
    {
        bulletManager.RemoveHitBox(&hitBox);
    }

    void update()
    {
        if (isDestroyed || hitBox.health <= 0)
        {
            destroy();
            return;
        }

        float currentTime = Time::getTime();

        if (state.player)
        {
            float dx = state.player->getX() - x;
            float dy = state.player->getY() - y;
            float distanceSquared = dx * dx + dy * dy;
            float distance = sqrt(distanceSquared);

            if (distance <= searchRadius)
            {
                rotation = Utils::Get_Angle_To_Point(
                    (Math::vec2){(float)state.player->getX(), (float)state.player->getY()},
                    (Math::vec2){x, y});

                // Движение к игроку, если он вне радиуса атаки
                if (distance > shootRadius)
                {
                    if (distance > 0)
                    {
                        dx = dx / distance * speed;
                        dy = dy / distance * speed;
                        x += dx;
                        y += dy;
                    }
                }

                if (currentTime >= nextFireTime && distance <= shootRadius * 1.2f)
                {
                    ShootAtPlayer();
                    nextFireTime = currentTime + 1.0f / fireRate;
                }
            }
        }

        hitBox.rec.x = x + width / 2.0f;
        hitBox.rec.y = y + height / 2.0f;
        hitBox.rotation = rotation;
    }

    void destroy()
    {
        if (isDestroyed)
            return;
        isDestroyed = true;
        bulletManager.RemoveHitBox(getHitBox());
    }

    void ShootAtPlayer()
    {
        if (!state.player)
            return;

        Math::vec2 bulletPos = {x, y};
        bulletManager.Shoot(bulletPos, rotation, bulletSpeed, 5.0f, TEAM_ENEMY);
    }

    void draw() override
    {
        Draw2D::Sprite(
            x, y, width, height,
            texture,
            Color::white, rotation);

        // Draw HP bar above the mob
        float hpBarWidth = CELL_SIZE;
        float hpBarHeight = 5.0f;
        float hpBarOffset = 10.0f;
        float hpPercentage = hitBox.health / 100.0f;

        // Background
        Draw2D::Rectangle(
            (Rect){x + width / 4.0f, y - hpBarOffset, hpBarWidth, hpBarHeight},
            Color::darkgray);
        // Health
        Draw2D::Rectangle(
            (Rect){x + width / 4.0f, y - hpBarOffset, hpBarWidth * hpPercentage, hpBarHeight},
            Color::red);
    }

    float getSearchRadius() const { return searchRadius; }
    void setSearchRadius(float radius) { searchRadius = radius; }
    float getX() const { return x; }
    float getY() const { return y; }
    HitBox *getHitBox() { return &hitBox; }

    float getFireRate() const { return fireRate; }
    void setFireRate(float rate) { fireRate = rate; }

    float getBulletSpeed() const { return bulletSpeed; }
    void setBulletSpeed(float speed) { bulletSpeed = speed; }
    bool isAlive() const { return !isDestroyed && hitBox.health > 0; }
};