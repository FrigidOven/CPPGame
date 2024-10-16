#include <iostream>
#include <raylib.h>
#include "ECS.h"

int main()
{
    const int screenWidth = 256 * 3;
    const int screenHeight = 224 * 3;
    
    InitWindow(screenWidth, screenHeight, "RaylibTest");
    SetTargetFPS(60);

    SpriteRendererSystem spriteRenderSystem;
    RigidBodySystem rigidBodySystem;
    ForceSystem forceSystem;
    SpeedLimiterSystem speedLimiterSystem;
    InputSystem inputSystem;

    Scene scene (spriteRenderSystem, rigidBodySystem, forceSystem, speedLimiterSystem, inputSystem);

    Texture2D texture = LoadTexture("Textures/Background.png");

    int testEntity1 = scene.CreateEntity();

    scene.AddComponent<Spatial>
        (
            testEntity1, 
            Vector2{ screenWidth / 2, screenHeight / 2 },
            0.0f
        );


    scene.AddComponent<Sprite>
    (
        testEntity1,
        &texture,
        Rectangle{ 0, 0, 256, 224 },
        256 * 3,
        224 * 3,
        1,
        0,
        1
    );
    scene.AddComponent<RigidBody>
    (
        testEntity1,
        1,
        Vector2{ 0, 0 },
        0,
        Vector2{ 0, 0 },
        0
    );
    scene.AddComponent<Force>
    (
        testEntity1,
        Vector2{ 10, 0 },
        0
    );
    scene.AddComponent<SpeedLimiter>
    (
        testEntity1,
        50,
        3
    );

    bool flippedDirection = false;
    while (WindowShouldClose() == false)
    {
        if (GetTime() > 5 && !flippedDirection)
        {
            scene.RemoveComponent<Force>(testEntity1);
            scene.AddComponent<Force>(testEntity1, Vector2{ -10, 0 }, -1);

            flippedDirection = true;
        }

        scene.Update();
    }
    
    CloseWindow();
    return 0;
}