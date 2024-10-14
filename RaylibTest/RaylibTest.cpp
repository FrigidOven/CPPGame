#include <iostream>
#include <raylib.h>
#include "ECS.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "RaylibTest");
    SetTargetFPS(60);

    Scene* scene = new Scene();

    Texture2D texture = LoadTexture("Textures/Stone.png");

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
        Rectangle{ 0, 0, 16, 16 },
        16 * 5,
        16 * 5,
        1,
        1
    );

    int testEntity2 = scene->CreateEntity();

    scene->AddSpatialComponent
    (
        testEntity2,
        Vector2{ screenWidth / 2, screenHeight / 2 },
        0
    );
    scene->AddSpriteComponent
    (
        testEntity2,
        &texture,
        Rectangle{ 0, 0, 16, 16 },
        16 * 5,
        16 * 5,
        1,
        1
    );

    while (WindowShouldClose() == false)
    {
        scene->GetSpatialComponent(testEntity1).SetPosition
        (
            { (screenWidth / 2) + ((screenWidth / 2) * cosf(GetTime())), (screenHeight / 2) + ((screenHeight / 2) * sinf(GetTime())) }
        );
        scene->GetSpatialComponent(testEntity2).SetPosition
        (
            { (screenWidth / 2) + ((screenWidth / 2) * sinf(GetTime())), (screenHeight / 2) + ((screenHeight / 2) * cosf(GetTime())) }
        );

        if (GetTime() > 5)
        {
            scene->RemoveSpriteComponent(testEntity1);
        }


        scene->Update();
    }

    CloseWindow();
    return 0;
}