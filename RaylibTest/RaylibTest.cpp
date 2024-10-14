#include <iostream>
#include <raylib.h>
#include "ECS.h"

int main()
{
    const int screenWidth = 256 * 3;
    const int screenHeight = 224 * 3;
    
    InitWindow(screenWidth, screenHeight, "RaylibTest");
    SetTargetFPS(60);

    Scene* scene = new Scene();

    Texture2D texture = LoadTexture("Textures/Background.png");

    int testEntity1 = scene->CreateEntity();

    scene->AddSpatialComponent
    (
        testEntity1,
        Vector2{ screenWidth / 2, screenHeight / 2 },
        0
    );
    scene->AddSpriteComponent
    (
        testEntity1,
        &texture,
        Rectangle{ 0, 0, 256, 224 },
        256 * 3,
        224 * 3,
        1,
        1
    );
    scene->AddVelocityComponent
    (
        testEntity1,
        Vector2{ 10, 0},
        5
    );

    while (WindowShouldClose() == false)
    {
        scene->Update();
    }
    
    CloseWindow();
    return 0;
}