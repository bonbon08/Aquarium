#include "raylib.h"
#include <stdlib.h>
#include <time.h>


#define NUM_FISH 50

typedef struct Fish {
    float size;
    Vector2 pos;
    int angle;
    bool toleft;
} Fish;

int main(void){
    int swidth = 1920;//GetScreenWidth();
    int sheight = 1080;//GetScreenHeight();
    srand(time(NULL));
    Color bgcolor = {81, 141, 214, 255};
    
    InitWindow(swidth, sheight, "Aquarium");

    Image basefish = LoadImage("fish.png");
    Texture2D fishTexture = LoadTextureFromImage(basefish);
    struct Fish Fishes[NUM_FISH];
    for(int i = 0; i < NUM_FISH; i++){
        Fishes[i].size = (float)((rand() % (200 - 100 + 1)) + 100);
        Fishes[i].pos = (Vector2){ 
            (float)(rand() % (int)(1920 - Fishes[i].size)), 
            (float)(rand() % (int)(1080 - Fishes[i].size)) 
        };
    };
    SetTargetFPS(60);
    ToggleFullscreen();
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(bgcolor);
        for(int i = 0; i < NUM_FISH; i++){
            Rectangle sourceRec = { 0.0f, 0.0f, (float)fishTexture.width, (float)fishTexture.height };   
            Rectangle destRec = { Fishes[i].pos.x, Fishes[i].pos.y, Fishes[i].size, Fishes[i].size }; 
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(fishTexture, sourceRec, destRec, origin, (float)Fishes[i].angle, WHITE);        };
        EndDrawing();
    }
    CloseWindow();
    return 0;
}