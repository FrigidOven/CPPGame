#include "Scene.h"
#include <iostream>

int main()
{
    const int screenWidth = 256 * 3;
    const int screenHeight = 224 * 3;
    
    InitWindow(screenWidth, screenHeight, "RaylibTest");
    SetTargetFPS(60);

    InputSystem inputSystem;
    ForceBasedMovementControllerSystem forceBasedMovementControllerSystem;
    VelocityBasedMovementControllerSystem velocityBasedMovementControllerSystem;
    ForceSystem forceSystem;
    FrictionSystem frictionSystem;
    AccelerationSystem accelerationSystem;
    VelocitySystem velocitySystem;
    ForceBasedSpeedLimiterSystem forceBasedSpeedLimiterSystem;
    StoppingForceSystem stoppingForceSystem;
    SpriteManagerSystem spriteMangerSystem;
    SpriteRendererSystem spriteRenderSystem;
   
    Scene scene
    (
        inputSystem,
        forceBasedMovementControllerSystem,
        velocityBasedMovementControllerSystem,
        forceSystem,
        frictionSystem,
        accelerationSystem,
        velocitySystem,
        forceBasedSpeedLimiterSystem,
        stoppingForceSystem,
        spriteMangerSystem,
        spriteRenderSystem
    );

    Texture2D backgroundSprite = LoadTexture("Textures/Background.png");
    Texture2D golemSprite = LoadTexture("Textures/GolemSprite.png");

    int testEntity0 = scene.CreateEntity(EntityTag::Untagged);

    scene.AddComponent<Spatial>(testEntity0, Vector2{ screenWidth / 2, screenHeight / 2 }, 0.0f);
    scene.AddComponent<BackgroundSprite>(testEntity0, &backgroundSprite, Rectangle{ 0, 0, screenWidth / 3, screenHeight / 3 }, screenWidth, screenHeight, 1, 0, 1);

    int testEntity1 = scene.CreateEntity(EntityTag::Player);

    scene.AddComponent<Spatial>(testEntity1, Vector2{ screenWidth / 2, screenHeight / 2 + (32 * 3) / 2 }, 0.0f);
    scene.AddComponent<MiddlegroundSprite>(testEntity1, &golemSprite, Rectangle{ 0, 34 * 2, 25, 34 }, 25 * 3, 34 * 3, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity1, Vector2Zero());
    scene.AddComponent<Acceleration>(testEntity1, Vector2Zero());
    scene.AddComponent<Mass>(testEntity1, 1.0f);
    scene.AddComponent<Force>(testEntity1, Vector2Zero());
    scene.AddComponent<Friction>(testEntity1, 0.8f);
    scene.AddComponent<ForceBasedMovementController>(testEntity1, 3000.0f, Input(Keyboard, KEY_UP, true), Input(Keyboard, KEY_LEFT, true), Input(Keyboard, KEY_DOWN, true), Input(Keyboard, KEY_RIGHT, true));
    scene.AddComponent<ForceBasedSpeedLimiter>(testEntity1, 300.0f);
    scene.AddComponent<SpriteManager>(testEntity1, SpriteOrientation::Down, SpriteState::Idle);

    int testEntity2 = scene.CreateEntity(EntityTag::Player);

    scene.AddComponent<Spatial>(testEntity2, Vector2{ screenWidth / 2, screenHeight / 2 - (32 * 3) / 2 }, 0.0f);
    scene.AddComponent<MiddlegroundSprite>(testEntity2, &golemSprite, Rectangle{ 0, 34 * 2, 25, 34 }, 25 * 3, 34 * 3, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity2, Vector2Zero());
    scene.AddComponent<VelocityBasedMovementController>(testEntity2, 300.0f, Input(Keyboard, KEY_W, true), Input(Keyboard, KEY_A, true), Input(Keyboard, KEY_S, true), Input(Keyboard, KEY_D, true));
    scene.AddComponent<VelocityBasedSpeedLimiter>(testEntity2, 300.0f);
    scene.AddComponent<SpriteManager>(testEntity2, SpriteOrientation::Up, SpriteState::Idle);

    while (!WindowShouldClose())
    {
        scene.Update();
    }

    CloseWindow();
    return 0;
}