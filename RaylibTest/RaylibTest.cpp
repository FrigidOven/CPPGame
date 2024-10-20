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
    ActionSystem actionSystem;

    Scene scene (spriteRenderSystem, velocitySystem, accelerationSystem, forceSystem, speedLimiterSystem, inputSystem, playerActionSystem, actionSystem);

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
        Input(Keyboard, KEY_UP,  false),
        Input(Keyboard, KEY_LEFT, false),
        Input(Keyboard, KEY_DOWN, false),
        Input(Keyboard, KEY_RIGHT, false)
    );

    while (WindowShouldClose() == false)
    {
        scene.Update();
    }
    
    CloseWindow();
    return 0;
}