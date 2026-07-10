#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_FISH 200

typedef struct Fish {
    float size;
    Vector2 pos;
    int angle;
    bool toleft;
    bool totop;
    float speed; 
    Color color;
} Fish;

int swidth = 1920;
int sheight = 1080;

void createFishes(Fish fishes[], int count) {
    for(int i = 0; i < count; i++) {
        fishes[i].size = (float)((rand() % (200 - 100 + 1)) + 100);
        fishes[i].pos = (Vector2){ 
            (float)(rand() % (int)(swidth - fishes[i].size)),
            (float)(rand() % (int)(sheight - fishes[i].size)) 
        };
        fishes[i].speed = (float)((rand() % (3 - 1 + 1)) + 1);
        fishes[i].angle = rand() % 26; 
        fishes[i].toleft = (rand() % 2 == 0);
        fishes[i].totop = (rand() % 2 == 0);
        
        fishes[i].color = (Color){ 
            (unsigned char)(rand() % 256), 
            (unsigned char)(rand() % 256), 
            (unsigned char)(rand() % 256), 
            255 
        };
    }
}

int main(void){
    srand(time(NULL));
    Color bgcolor = {81, 141, 214, 255};
    
    InitWindow(swidth, sheight, "Aquarium");
    swidth = GetMonitorWidth(GetCurrentMonitor());
    sheight = GetMonitorHeight(GetCurrentMonitor());   
    Image basefish = LoadImage("fish.png");
    Color *pixels = (Color *)basefish.data;
    
    for (int i = 0; i < basefish.width * basefish.height; i++) {
        if (pixels[i].r > 200 && pixels[i].g > 180 && pixels[i].b < 100) {
            pixels[i].r = 255;
            pixels[i].g = 255;
            pixels[i].b = 255;
        }
    }
    
    Texture2D fishTexture = LoadTextureFromImage(basefish);
    UnloadImage(basefish); 
    
    Fish Fishes[NUM_FISH];
    createFishes(Fishes, NUM_FISH);

    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(bgcolor);
        
        for(int i = 0; i < NUM_FISH; i++){
            float radians = Fishes[i].angle * DEG2RAD;
            float speedX = fabsf(cosf(radians) * Fishes[i].speed);
            float speedY = fabsf(sinf(radians) * Fishes[i].speed);
            if (Fishes[i].toleft == false){
                if (Fishes[i].pos.x + speedX < swidth - Fishes[i].size) {
                    Fishes[i].pos.x += speedX;
                }
                else {
                    Fishes[i].toleft = true;
                }
            } else {
                if (Fishes[i].pos.x - speedX > 0) { 
                    Fishes[i].pos.x -= speedX;
                }
                else {
                    Fishes[i].toleft = false;
                }
            }
            if (Fishes[i].totop == false){
                if (Fishes[i].pos.y + speedY < sheight - Fishes[i].size) {
                    Fishes[i].pos.y += speedY;
                }
                else {
                    Fishes[i].totop = true;
                }
            } else {
                if (Fishes[i].pos.y - speedY > 0) {
                    Fishes[i].pos.y -= speedY;
                }
                else {
                    Fishes[i].totop = false;
                }
            }
            Rectangle sourceRec = { 0.0f, 0.0f, (float)fishTexture.width, (float)fishTexture.height };   
            Rectangle destRec = { Fishes[i].pos.x, Fishes[i].pos.y, Fishes[i].size, Fishes[i].size }; 
            Vector2 origin = { Fishes[i].size / 2.0f, Fishes[i].size / 2.0f };
            destRec.x += Fishes[i].size / 2.0f;
            destRec.y += Fishes[i].size / 2.0f;

            float drawAngle = (float)Fishes[i].angle;

            if (Fishes[i].toleft == false) {
                sourceRec.width = -sourceRec.width;
                if (Fishes[i].totop) drawAngle = -drawAngle; 
            } 
            else {
                if (Fishes[i].totop == false) drawAngle = -drawAngle;
            } 
            
            DrawTexturePro(fishTexture, sourceRec, destRec, origin, drawAngle, Fishes[i].color);        
        }
        EndDrawing();
    }
    
    UnloadTexture(fishTexture);
    CloseWindow();
    return 0;
}