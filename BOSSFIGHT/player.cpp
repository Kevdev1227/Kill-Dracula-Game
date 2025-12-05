#include "game.h"
#include "player.h"
#include "math.h"

class Dracula;
class Player;
extern Dracula* g_dracula;
extern Player* g_player;

Player::Player(Vector2 initial_pos) {
    g_player = this;
    position = initial_pos;

    idle_texture = LoadTexture("assets/richter_idle.png");
    jumping_texture = LoadTexture("assets/richter_jump.png");
    falling_texture = LoadTexture("assets/richter_fall.png");
    attack_texture = LoadTexture("assets/richter_attack.png");
}

void Player::take_damage() {
    hearts -= 1;
}

void Player::attack(Sound whiphit_sound) {
    if (attackCooldown <= 0.0f && g_dracula != nullptr) {

        Vector2 player_center = { position.x + 34.5f, position.y + 60.f }; 
        Vector2 dracula_center = { g_dracula->position.x + 64.f, g_dracula->position.y + 105.5f }; 

        float dx = dracula_center.x - player_center.x;
        float dy = dracula_center.y - player_center.y;
        float distance = sqrt(dx * dx + dy * dy);

        float attackRange = 280.0f; 

        if (distance <= attackRange) {
            g_dracula->take_damage(100);
            PlaySound(whiphit_sound);
        }
        attacking = true;
        attackCooldown = attackRate;
        attackAnimTimer = attackAnimTime;
    }
}

void Player::move(Sound whipswing_sound, Sound whiphit_sound) {
    if (IsKeyDown(KEY_A)) {
        velocity.x = -speed;
        flipped = true;
    }
    else if (IsKeyDown(KEY_D)) {
        velocity.x = speed;
        flipped = false;
    }
    else {
        velocity.x = 0.f;
    }

    if (IsKeyDown(KEY_SPACE) && isOnGround) {
        velocity.y = -600.f;
        isOnGround = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        attack(whiphit_sound);
        PlaySound(whipswing_sound);
    }
}

void Player::update(float dt) {
    float gravity = 800.f;
    velocity.y += gravity * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;


    if (attackCooldown > 0)
        attackCooldown -= dt;

    if (attacking) {
        attackAnimTimer -= dt;
        if (attackAnimTimer <= 0)
            attacking = false;
    }

    if (position.y >= SCREEN_HEIGHT - 118) {
        position.y = SCREEN_HEIGHT  - 118;
        velocity.y = 0.f;
        isOnGround = true;
    }
}


void Player::draw() {
    if (attacking) {
        if (flipped)
            DrawTextureRec(attack_texture, { 0,0,-(float)attack_texture.width,120 }, Vector2{ position.x - 120.f, position.y }, WHITE);
        else
            DrawTexture(attack_texture, (int)position.x, (int)position.y, WHITE);
    }
    else {
        if (isOnGround || velocity.y == 0) {
            if (flipped)
                DrawTextureRec(idle_texture, { 0,0,-69.f,120.f }, position, WHITE);
            else
                DrawTexture(idle_texture, (int)position.x, (int)position.y, WHITE);
        }
        else if (velocity.y < 0) {
            if (flipped)
                DrawTextureRec(jumping_texture, { 0,0,-69.f,120.f }, position, WHITE);
            else
                DrawTexture(jumping_texture, (int)position.x, (int)position.y, WHITE);
        }
        else {
            if (flipped)
                DrawTextureRec(falling_texture, { 0,0,-69.f,120.f }, position, WHITE);
            else
                DrawTexture(falling_texture, (int)position.x, (int)position.y, WHITE);
        }
    }
}