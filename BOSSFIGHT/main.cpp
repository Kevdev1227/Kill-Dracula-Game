#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"

#include "game.h"
#include "dracula.h"
#include "player.h"

using namespace std;


// MAIN
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Kill Dracula");
    InitAudioDevice();
    SetTargetFPS(60);

    bool gameOver = false;
    bool gameWin = false;
    float quitTimer = 0.0f;

    Texture2D dracula_texture = LoadTexture("assets/dracula.png");
    Texture2D heart_texture = LoadTexture("assets/heart.png");
    Texture2D healthbar_texture = LoadTexture("assets/healthbar.png");
    Texture2D bar_texture = LoadTexture("assets/bar.png");
    Texture2D death_texture = LoadTexture("assets/death.png");
    Texture2D gamewin_texture = LoadTexture("assets/game.png");
    Texture2D dracula_lair = LoadTexture("assets/draculalair.png");
    Texture2D floor_tile = LoadTexture("assets/floortile.png");

    Sound death_sound = LoadSound("assets/secunda.wav");
    Sound battle_sound = LoadSound("assets/battle.wav");
    Sound whiphit_sound = LoadSound("assets/whiphit.wav");
    Sound whipswing_sound = LoadSound("assets/whipswing.wav");
    Sound ff7_sound = LoadSound("assets/ff7.wav");
    Sound playerdamage = LoadSound("assets/playerdamage.wav");

    SetSoundVolume(battle_sound, 0.1);

    heart_texture.height = 40; 
    heart_texture.width = 40;

    Dracula the_dracula(Vector2{ 650.f, 237.f });
    Player the_player(Vector2{ 0.f, 290.f });

    PlaySound(battle_sound);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (gameOver || gameWin) {
            quitTimer += dt;
            if (quitTimer >= 10.0f) {
                break; // ends while loop
            }
        }

        if (the_player.hearts > 0) {
            the_player.move(whipswing_sound, whiphit_sound);
            the_player.update(dt);
        }


        // Dracula attacks player while standing still
        the_dracula.try_attack(dt, playerdamage);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(dracula_lair, 0, 0, WHITE);
        

       if (the_player.hearts > 0) {
            the_player.draw();
        }


        // health bar stuff
        float scale = the_dracula.health / 5000.f;
        Rectangle background_rect = { 275.f, 7.f, healthbar_texture.width - 85, 20 };
        Rectangle bar_rect = { 275.f, 7.f, background_rect.width * scale, 20 };
        DrawRectangleRounded(background_rect, 0.f, 20, { 113, 0, 0, 255 });
        DrawRectangleRounded(bar_rect, 0.f, 20, { 255, 0, 0, 255 });
        DrawTexture(healthbar_texture, (int)265.f, -8.f, WHITE);

        // Dracula health
        if (the_dracula.health <= 0) {
            DrawText("Dead", SCREEN_WIDTH / 2, 7, 20, WHITE);
            if (!IsSoundPlaying(ff7_sound))
                PlaySound(ff7_sound);
        }
        else {
            string dracula_health_string = to_string(the_dracula.health) + "/5000";
            DrawText(dracula_health_string.c_str(), SCREEN_WIDTH / 2, 7, 20, WHITE);
        }
        // Player hearts
        if (the_player.hearts >= 1) DrawTexture(heart_texture, 0, 0, WHITE);
        if (the_player.hearts >= 2) DrawTexture(heart_texture, 40, 0, WHITE);
        if (the_player.hearts >= 3) DrawTexture(heart_texture, 80, 0, WHITE);

        the_dracula.draw(dracula_texture);
        

        // Dracula death
        if (the_dracula.health <= 0) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 200 });
            DrawTexture(gamewin_texture, SCREEN_WIDTH / 2 - gamewin_texture.width / 2, SCREEN_HEIGHT / 2 - gamewin_texture.height / 2, WHITE);
            
            gameWin = true;
        }

        // Player death
        
        if (!gameWin && the_player.hearts <= 0) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 200 });
            DrawTexture(death_texture, 0, 150, WHITE);
           
            
            gameOver = true;

            StopSound(battle_sound);
            if (!IsSoundPlaying(death_sound))
                PlaySound(death_sound);


        }

        EndDrawing();
    }


}
