#include "raylib.h"
#include <stdlib.h>
#include <time.h>


#define NUM_FISH 1

typedef struct Fish {
    Texture2D picture;
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
    int Fishsize = (rand() % (200 - 100 + 1)) + 100;
    ImageResizeNN(&basefish, Fishsize, Fishsize);
    Texture2D fish = LoadTextureFromImage(basefish);
    struct Fish Fishes[NUM_FISH];
    for(int i = 0; i < NUM_FISH; i++){
        Fishes[i].picture = fish;
        Fishes[i].pos = (Vector2){ 500, 500};
    };
    SetTargetFPS(60);
    ToggleFullscreen();
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(bgcolor);
        for(int i = 0; i < NUM_FISH; i++){
            DrawTextureV(Fishes[i].picture, Fishes[i].pos, WHITE);
        };
        EndDrawing();
    }
    CloseWindow();
    return 0;
}