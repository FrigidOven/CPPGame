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

    while (!WindowShouldClose())
    {
        scene.Update();
    }
    
    CloseWindow();
    return 0;
}