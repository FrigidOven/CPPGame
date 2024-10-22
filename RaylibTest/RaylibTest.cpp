#include "ECS.h"

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
    VelocityBasedSpeedLimiterSystem velocityBasedSpeedLimiterSystem;
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
        velocityBasedSpeedLimiterSystem,
        spriteRenderSystem
    );

    Texture2D texture = LoadTexture("Textures/Background.png");

    int testEntity1 = scene.CreateEntity();

    scene.AddComponent<Spatial>(testEntity1, Vector2{ screenWidth / 2, screenHeight / 2 + (32 * 3) / 2 }, 0.0f);
    scene.AddComponent<MiddlegroundSprite>(testEntity1, &texture, Rectangle{ 0, 0, 32, 32 }, 32 * 3, 32 * 3, 8, 0, 5);
    scene.AddComponent<Velocity>(testEntity1, Vector2Zero());
    scene.AddComponent<Acceleration>(testEntity1, Vector2Zero());
    scene.AddComponent<Mass>(testEntity1, 1.0f);
    scene.AddComponent<Force>(testEntity1, Vector2Zero());
    scene.AddComponent<Friction>(testEntity1, 0.8f);
    scene.AddComponent<ForceBasedMovementController>(testEntity1, 2000.0f, Input(Keyboard, KEY_UP, true), Input(Keyboard, KEY_LEFT, true), Input(Keyboard, KEY_DOWN, true), Input(Keyboard, KEY_RIGHT, true));
    scene.AddComponent<ForceBasedSpeedLimiter>(testEntity1, 300.0f);

    while (!WindowShouldClose())
    {
        scene.Update();
    }
    
    CloseWindow();
    return 0;
}