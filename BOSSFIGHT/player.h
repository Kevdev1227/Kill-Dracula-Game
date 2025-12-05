#pragma once
#include "raylib.h"
#include "dracula.h"

class Player;
inline Player* g_player;

// PLAYER CLASS
class Player {
public:
    Vector2 position;
    Vector2 velocity = { 0.f, 0.f };
    int hearts = 3;
    float speed = 300.0f;
    bool isOnGround = true;
    bool flipped = false;
    bool attacking = false;

    float attackCooldown = 0.0f;
    float attackRate = 0.4f;
    float attackAnimTime = 0.15f;
    float attackAnimTimer = 0.0f;

    Texture2D idle_texture;
    Texture2D jumping_texture;
    Texture2D falling_texture;
    Texture2D attack_texture;

    Player(Vector2 initial_pos);
    void take_damage();
    void attack(Sound whiphit_sound);
    void move(Sound whipswing_sound, Sound whiphit_sound);
    void update(float dt);
    void draw();
};