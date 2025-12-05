#pragma once
#include "raylib.h"
#include "player.h"

class Dracula;
inline Dracula* g_dracula;

// DRACULA CLASS
class Dracula {
public:
    Vector2 position;
    int health = 5000;

    // attack variables
    bool charging = false;
    float chargeTime = 0.15f;
    float chargeTimer = 0.0f;
    float attackCooldown = 0.0f;
    float attackRate = 0.0f; // 0.2 in seconds
    float attackRange = 110.0f;
    float speed = -4.0f;

 


    // Constructor
    Dracula(Vector2 pos);

    void take_damage(int dmg);
    void try_attack(float dt, Sound playerdamage_sound);

    void draw(Texture2D dracula_texture);

};