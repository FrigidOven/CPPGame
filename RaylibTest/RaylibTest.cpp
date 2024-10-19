#include "ECS.h"

int main()
{
    const int screenWidth = 256 * 3;
    const int screenHeight = 224 * 3;
    
    InitWindow(screenWidth, screenHeight, "RaylibTest");
    SetTargetFPS(60);

    SpriteRendererSystem spriteRenderSystem;
    VelocitySystem velocitySystem;
    AccelerationSystem accelerationSystem;
    ForceSystem forceSystem;
    SpeedLimiterSystem speedLimiterSystem;
    InputSystem inputSystem(InputMode::Default);
    PlayerActionSystem playerActionSystem;

    Scene scene (spriteRenderSystem, velocitySystem, accelerationSystem, forceSystem, speedLimiterSystem, inputSystem, playerActionSystem);

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
        Vector2{ 0.0f, 0.0f },
        0,
        Vector2{ 0.0f, 0.0f },
        0.0f,
        0.8f
    );
    scene.AddComponent<Force>
    (
        testEntity1,
        Vector2{ 0, 0 },
        Vector2{ 0, 0 },
        0.0f,
        0.0f
    );
    scene.AddComponent<SpeedLimiter>
    (
        testEntity1,
        300,
        3
    );
    scene.AddComponent<PlayerInputListener>
    (
        testEntity1,
        KEY_UP,
        KEY_LEFT,
        KEY_DOWN,
        KEY_RIGHT
    );

    while (WindowShouldClose() == false)
    {
        scene.Update();
    }
    
    CloseWindow();
    return 0;
}