#include "Game.h"
#include "GameConstants.h"
#include <iostream>

int main()
{  
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RaylibTest");
    SetTargetFPS(144);

    Game game;
    Scene& scene = game.GetCurrentScene();

    Texture2D backgroundSprite = LoadTexture("Textures/Grass.png");
    Texture2D golemSprite = LoadTexture("Textures/Player.png");

    int testEntity0 = scene.CreateEntity();
    Tag& entityTag0 = scene.GetComponent<Tag>(testEntity0);
    entityTag0.entityGroup = EntityGroup::Surface;
    entityTag0.entityType = EntityType::GrassSurface;

    scene.AddComponent<Spatial>(testEntity0, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity0, 0, &backgroundSprite, Rectangle{ 0, 0, 256, 224 }, 256 * PIXEL_SIZE, 224 * PIXEL_SIZE, 1, 0, 1);

    int testEntity1 = scene.CreateEntity();
    Tag& entityTag1 = scene.GetComponent<Tag>(testEntity1);
    entityTag1.entityGroup = EntityGroup::Player;
    entityTag1.entityType = EntityType::Player;
    entityTag1.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity1, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (32 * PIXEL_SIZE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity1, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 32 * PIXEL_SIZE, 32 * PIXEL_SIZE, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity1, Vector2Zero());
    scene.AddComponent<Acceleration>(testEntity1, Vector2Zero());
    scene.AddComponent<Mass>(testEntity1, 25.0f);
    scene.AddComponent<ForceReceiver>(testEntity1);
    scene.AddComponent<Friction>(testEntity1, 0.8f);
    scene.AddComponent<Controller>(testEntity1, 
        Input(ControlType::Keyboard, KEY_UP),
        Input(ControlType::Keyboard, KEY_LEFT),
        Input(ControlType::Keyboard, KEY_DOWN),
        Input(ControlType::Keyboard, KEY_RIGHT));
    scene.AddComponent<MovementController>(testEntity1, MovementMode::ForceBased, 800.0f);
    scene.AddComponent<SpeedLimiter>(testEntity1, 1.0f);
    scene.AddComponent<SpriteManager>(testEntity1);

    scene.AddComponent<FollowCamera>(static_cast<int>(SpecialEntities::Camera), testEntity1, Vector2Zero());
    
    bool impulseAdded = false;

    while (!WindowShouldClose())
    {
        std::cout << "Velocity is: " << Vector2Length(scene.GetComponent<Velocity>(testEntity1).velocity) << "\n";
        game.Update();

        if (!impulseAdded && GetTime() > 3.0f)
        {
            impulseAdded = scene.AddComponent<Impulse>(testEntity1, Vector2(1000.0f, 0.0f), 0.25f);
        }
    }

    CloseWindow();
    return 0;
}