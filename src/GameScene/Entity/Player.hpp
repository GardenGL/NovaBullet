#pragma once

#include "../World/Constants.hpp"
#include "../World/Utils.hpp"
#include <Engine.hpp>
#include "gameobject.hpp"
#include "../Camera2D.hpp"
#include "BulletManager.h"

class Player : public GameObject
{
private:
    float x, y, width, height, speed, rotation;
    int verticalVelocity;
    Math::vec2 directionVectors[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    HitBox hitBox;

    int fullAmmo = 30;
    int currentAmmo = 30;

    float reloadTime = 0.5f;
    float currentReloadTime;
    bool isReloading;
    float respawnTime = 3.0f; // Время перед респавном
    float currentRespawnTime;
    bool isDead;

public:
    Player() : GameObject("Player")
    {
    }

    Player(float x, float y, float w, float h, float speed)
        : GameObject("Player"), x(x), y(y), width(w), height(h), speed(speed),
          verticalVelocity(0), isDead(false)
    {
        hitBox = (HitBox){(Rect){x, y, w, h}, 100, 0.0f, TEAM_FRIENDLY, this}; // Указываем себя как владельца
        bulletManager.AddHitBox(getHitBox());
    }

    ~Player()
    {
        bulletManager.RemoveHitBox(&hitBox);
    }

    void update() override
    {
        if (isDead)
        {
            currentRespawnTime -= Time::getDelta();
            if (currentRespawnTime <= 0)
            {
                respawn();
            }
            return;
        }

        move(Inputs::KEY_W, Inputs::KEY_S, Inputs::KEY_A, Inputs::KEY_D);

        hitBox.rec.x = x + width / 2.0f;
        hitBox.rec.y = y + height / 2.0f;
        hitBox.rotation = rotation;

        if (Inputs::IsKeyPressed(Inputs::KEY_R) && !isReloading)
        {
            currentReloadTime = reloadTime;
            isReloading = true;
            Reload();
        }
        double time = Time::getTime();
        static float fireRate = 8.0f;
        static float nextTimeToFire = 0.0f;

        if (Inputs::IsKeyDown(Inputs::MOUSE_BUTTON_LEFT) && time >= nextTimeToFire && !isReloading && currentAmmo > 0)
        {
            currentAmmo--;
            nextTimeToFire = time + 1.0f / fireRate;

            float screenX = static_cast<float>(x + width / 2.0f);
            float screenY = static_cast<float>(y + height / 2.0f);

            Math::vec2 CenterPos = (Math::vec2){screenX , screenY };

            Math::vec2 worldMousePos = main_camera.GetScreenToWorld(Math::vec2(Inputs::x, Inputs::y), Math::vec2(Window::width, Window::height));

            int blockX = static_cast<int>(worldMousePos.x / GameConstants::CELL_SIZE);
            int blockY = static_cast<int>(worldMousePos.y / GameConstants::CELL_SIZE);

            float rotati = Utils::Get_Angle_To_Point(worldMousePos, CenterPos);

            bulletManager.Shoot(CenterPos, rotati, 8, 25.0f, TEAM_FRIENDLY);
        }

        if (isReloading)
        {
            currentReloadTime -= Time::getDelta();
            if (currentReloadTime <= 0)
            {
                isReloading = false;
            }
        }

        focusCamera(main_camera.position);
    }

    void drawUI() override
    {
        Draw2D::Font::Text(TextFormat("%d / %d", currentAmmo, fullAmmo), 100, 880, 40.0f, Draw2D::Font::ALIGN_CENTER, Color::white);
        HealthBar_Draw(600.0f, 850.0f);
    }

    void draw() override
    {
        if (isDead)
            return;

        const Math::mat4x4 &viewMatrix = main_camera.GetViewMatrix();

        Math::vec2 worldMousePos = main_camera.GetScreenToWorld(Math::vec2(Inputs::x, Inputs::y), Math::vec2(Window::width, Window::height));

        Math::vec2 playerCenter = {x + width / 2, y + height / 2};
        rotation = Utils::Get_Angle_To_Point(worldMousePos, playerCenter);

        Draw2D::Sprite(

            x, y, width, height,
            
            ResourceManager::GetTexture("SpaceShip"),
            Color::white, rotation);

        
    }

    void HealthBar_Draw(float x, float y)
    {
        if (isDead)
        {
            Draw2D::Font::Text("RESPAWNING...", Window::width / 2, Window::height / 2, 60.0f, Draw2D::Font::ALIGN_CENTER, Color::red);
            return;
        }

        Draw2D::Rectangle((Rect){x, y, 410, 35}, Color::darkgray);
        Draw2D::Rectangle((Rect){x + 5, y + 5, hitBox.health * 4.0f, 25}, (Math::vec4){230, 41, 55, 100});
        Draw2D::Font::Text(TextFormat("Health: %d", hitBox.health), x + 205, y + 25, 20.0f, Draw2D::Font::ALIGN_CENTER, Color::white);
    }

    void Reload()
    {
        currentAmmo = fullAmmo;
    }

    void respawn()
    {
        isDead = false;
        hitBox.health = 100;
        currentAmmo = fullAmmo;

        // Рандомная позиция для респавна
        x = Random::Float(0.0f, GameConstants::WORLD_WIDTH - width);
        y = Random::Float(0.0f, GameConstants::WORLD_HEIGHT - height);

        hitBox.rec.x = x + width / 2.0f;
        hitBox.rec.y = y + height / 2.0f;

        bulletManager.AddHitBox(getHitBox());
    }

    void takeDamage(int damage)
    {
        if (isDead)
            return;

        hitBox.health -= damage;
        if (hitBox.health <= 0)
        {
            isDead = true;
            currentRespawnTime = respawnTime;
            bulletManager.RemoveHitBox(getHitBox());
        }
    }

    bool isAlive() const { return !isDead; }

    void focusCamera(Math::vec2 &cameraPos) const
    {
        if (isDead)
            return;

        float targetX = x - Window::width / 2.0f + width / 2.0f;
        float targetY = y - Window::height / 2.0f + height / 2.0f;

        targetX = Utils::clamp(targetX, 0.0f, static_cast<float>(GameConstants::WORLD_WIDTH - Window::width));
        targetY = Utils::clamp(targetY, 0.0f, static_cast<float>(GameConstants::WORLD_HEIGHT - Window::height));

        cameraPos.x += (targetX - cameraPos.x) * 0.1f;
        cameraPos.y += (targetY - cameraPos.y) * 0.1f;
    }

    RectangleF getRect() const
    {
        return {x, y, x + width - 1, y + height - 1};
    }

    void tryMove(int dx, int dy, GameState &state)
    {
        x += dx;
        y += dy;

        x = Utils::clamp(x, 0.0f, static_cast<float>(GameConstants::WORLD_WIDTH - width));
        y = Utils::clamp(y, 0.0f, static_cast<float>(GameConstants::WORLD_HEIGHT - height));
    }

    void move(int jumpKey, int downKey, int leftKey, int rightKey)
    {
        const int controls[4] = {jumpKey, downKey, leftKey, rightKey};

        for (int k = 0; k < speed; k++)
        {
            if (Inputs::IsKeyDown(controls[0]))
            {
                tryMove(0, -1, state);
            }
            if (Inputs::IsKeyDown(controls[1]))
            {
                tryMove(0, 1, state);
            }
            if (Inputs::IsKeyDown(controls[2]))
            {
                tryMove(-1, 0, state);
            }
            if (Inputs::IsKeyDown(controls[3]))
            {
                tryMove(1, 0, state);
            }
        }
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    int getCellX() const { return x / GameConstants::CELL_SIZE; }
    int getCellY() const { return y / GameConstants::CELL_SIZE; }
    HitBox *getHitBox() { return &hitBox; }
};