#include "math.h"
#include "dracula.h"
#include <iostream>
using namespace std;

class Dracula;
class Player;
extern Dracula* g_dracula;
extern Player* g_player;

Dracula::Dracula(Vector2 pos) {
    g_dracula = this;
    position = pos;
}

void Dracula::take_damage(int dmg) {
    health -= dmg;
}

// Draculas attack function
void Dracula::try_attack(float dt, Sound playerdamage_sound) {
    if (g_player->hearts <= 0) {
        return;
    }
    
    if (attackCooldown > 0)
        attackCooldown -= dt;

    if (charging) {
        chargeTimer -= dt;

        if (chargeTimer <= 0) {
            charging = false;

            Vector2 dracula_size = { 128.f, 211.f };
            float dx = g_player->position.x - (position.x + dracula_size.x / 2.f);
            float dy = g_player->position.y - (position.y + dracula_size.y / 2.f);
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < attackRange) {
                g_player->take_damage();
                
                if (!IsSoundPlaying(playerdamage_sound))
                    PlaySound(playerdamage_sound);
            }
            attackCooldown = attackRate;
        }

        return;
    }

    if (attackCooldown <= 0) {
        Vector2 dracula_size = { 128.f, 211.f };
        float dx = g_player->position.x - (position.x + dracula_size.x / 2.f);
        float dy = g_player->position.y - (position.y + dracula_size.y / 2.f);
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < attackRange) {
            charging = true;
            chargeTimer = chargeTime;
        }
    }

    }
void Dracula::draw(Texture2D dracula_texture) {

    if (position.x < 50.0f || position.x > 670.0f) {
        speed *= -1.0f;
    }
    
    
    position.x += speed;

    if (health > 0) {

        if (speed < 0.0f) {
            DrawTexture(dracula_texture, (int)position.x, (int)position.y, WHITE);
        }
        else {
            DrawTextureRec(dracula_texture, { 0,0,-(float)dracula_texture.width,(float)dracula_texture.height }, position, WHITE);
        }

        // dracula attack range circle
        Vector2 dracula_size = { 128.f, 211.f };
        DrawCircleLines(
            position.x + dracula_size.x / 2.f,
            position.y + dracula_size.y / 2.f,
            attackRange, RED
        );
    }


    // Attack range for Dracula
    Vector2 dracula_size = { 128.f, 211.f };

    // Draw circle only if Dracula is not charging and alive
    if (health > 0 && !charging) {
        DrawCircleLines(
            position.x + dracula_size.x / 2.f,
            position.y + dracula_size.y / 2.f,
            attackRange, RED
        );
    }

    // Dracula charge
    if (health > 0) {
        if (charging) {
            DrawCircleLines(
                position.x + dracula_size.x / 2.f,
                position.y + dracula_size.y / 2.f,
                attackRange, YELLOW
            );
        }
        else {
            DrawCircleLines(
                position.x + dracula_size.x / 2.f,
                position.y + dracula_size.y / 2.f,
                attackRange, RED
            );
        }
    }
}
