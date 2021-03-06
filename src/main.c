#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente profe");
    SetTargetFPS(60);
    int frames = 0;

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,50);

    // Main loop
    while(!WindowShouldClose()){
        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta);

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Presente profe!",20,20,20,LIGHTGRAY);

            if(sta->n_enemies != 0)
            {
                DrawText(FormatText("Tiempo: %03i segundos", frames/60),20,40,20,RED);
                DrawText(FormatText("Enemigos restantes: %03i", sta->n_enemies),20,60,20,RED);
                frames+=1;
            }else
            {
                DrawText(FormatText("You win! \nTiempo: %03i segundos", frames/60),100,150,60,RED);
            }

        EndDrawing();
    }

    // Close window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
