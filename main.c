#include "raylib.h"



int main(void){
    int swidth = 1920;//GetScreenWidth();
    int sheight = 1080;//GetScreenHeight();
    Color bgcolor = {81, 141, 214, 255};

    InitWindow(swidth, sheight, "Aquarium");
    SetTargetFPS(60);
    ToggleFullscreen();
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(bgcolor);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}