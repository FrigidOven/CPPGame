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

    scene.AddComponent<Spatial>(testEntity1, Vector2{ screenWidth / 2, screenHeight / 2 + (32*3)/2}, 0.0f);
    scene.AddComponent<Sprite>(testEntity1, &texture, Rectangle{ 0, 0, 32, 32}, 32 * 3, 32 * 3, 8, 5);
    scene.AddComponent<RigidBody>(testEntity1, 1, Vector2{ 0.0f, 0.0f }, 0, Vector2{ 0.0f, 0.0f }, 0.0f, 0.8f);
    scene.AddComponent<Force>(testEntity1, Vector2{ 0, 0 }, Vector2{ 0, 0 }, 0.0f, 0.0f);
    scene.AddComponent<SpeedLimiter>(testEntity1, 300, 3);
    scene.AddComponent<PlayerInputListener>(testEntity1, Input(Keyboard, KEY_UP,  true), Input(Keyboard, KEY_LEFT, true), Input(Keyboard, KEY_DOWN, true), Input(Keyboard, KEY_RIGHT, true));

    int testEntity2 = scene.CreateEntity();

    scene.AddComponent<Spatial>(testEntity2, Vector2{ screenWidth / 2, screenHeight / 2 - (32*3)/2}, 0.0f);
    scene.AddComponent<Sprite>(testEntity2, &texture, Rectangle{ 0, 192, 32, 32}, 32 * 3, 32 * 3, 8, 5);
    scene.AddComponent<RigidBody>(testEntity2, 1, Vector2{ 0.0f, 0.0f }, 0, Vector2{ 0.0f, 0.0f }, 0.0f, 0.8f);
    scene.AddComponent<Force>(testEntity2, Vector2{ 0, 0 }, Vector2{ 0, 0 }, 0.0f, 0.0f);
    scene.AddComponent<SpeedLimiter>(testEntity2, 300, 3);
    scene.AddComponent<PlayerInputListener>(testEntity2, Input(Keyboard, KEY_W, true), Input(Keyboard, KEY_A, true), Input(Keyboard, KEY_S, true), Input(Keyboard, KEY_D, true));


    while (!WindowShouldClose())
    {
        if (5.0f < GetTime() &&  GetTime() < 5.5f)
            scene.GetComponent<PlayerInputListener>(testEntity1).inputListener.BlockForSeconds(scene.GetComponent<PlayerInputListener>(testEntity1).up, 5.0f);

        scene.Update();
    }
    
    CloseWindow();
    return 0;
}