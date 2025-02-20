#include "Game.h"

int main()
{  
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "RaylibTest");
    SetTargetFPS(144);

    Game game;
    Scene& scene = game.GetCurrentScene();

    Texture2D backgroundSprite = LoadTexture("Textures/Grass.png");
    Texture2D golemSprite = LoadTexture("Textures/Player.png");

    int testEntity0 = scene.CreateEntity();
    Tag& entityTag0 = scene.GetComponent<Tag>(testEntity0);
    entityTag0.entityGroup = EntityGroup::Surface;
    entityTag0.entityType = EntityType::GrassSurface;

    scene.AddComponent<Spatial>(testEntity0, Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity0, 0, &backgroundSprite, Rectangle{ 0, 0, 256, 224 }, 1, 1, 1, 0, 1);

    int testEntity1 = scene.CreateEntity();
    Tag& entityTag1 = scene.GetComponent<Tag>(testEntity1);
    entityTag1.entityGroup = EntityGroup::Player;
    entityTag1.entityType = EntityType::Player;
    entityTag1.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity1, Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 + 16}, 0.0f);
    scene.AddComponent<Sprite>(testEntity1, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 1, 1, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity1);
    scene.AddComponent<Acceleration>(testEntity1);
    scene.AddComponent<Rigidbody>(testEntity1, 25.0f);
    scene.AddComponent<Friction>(testEntity1, 0.8f);
    scene.AddComponent<Controller>(testEntity1, 
        Input(ControlType::Keyboard, KEY_UP),
        Input(ControlType::Keyboard, KEY_LEFT),
        Input(ControlType::Keyboard, KEY_DOWN),
        Input(ControlType::Keyboard, KEY_RIGHT));
    scene.AddComponent<MovementController>(testEntity1, MovementMode::ForceBased, 800.0f , 1.0f);
    scene.AddComponent<SpriteManager>(testEntity1);


    int testEntity2 = scene.CreateEntity();
    Tag& entityTag2 = scene.GetComponent<Tag>(testEntity2);
    entityTag2.entityGroup = EntityGroup::Player;
    entityTag2.entityType = EntityType::Player;
    entityTag2.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity2, Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 - 16 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity2, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 1, 1, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity2);
    scene.AddComponent<Controller>(testEntity2,
        Input(ControlType::Keyboard, KEY_UP),
        Input(ControlType::Keyboard, KEY_LEFT),
        Input(ControlType::Keyboard, KEY_DOWN),
        Input(ControlType::Keyboard, KEY_RIGHT));
    scene.AddComponent<MovementController>(testEntity2, MovementMode::VelocityBased, 1.0f, 1.0f);
    scene.AddComponent<SpriteManager>(testEntity2);

    scene.AddComponent<FollowCamera>(static_cast<int>(SpecialEntities::Camera), testEntity0, Vector2Zero());
    
    bool impulseAdded = false;

    while (!WindowShouldClose())
    {
        game.Update();

        if (!impulseAdded && GetTime() > 2.0f)
            impulseAdded = scene.AddComponent<Impulse>(testEntity1, Vector2(500.0f, 0.0f), 0.15f);
    }

    CloseWindow();
    return 0;
}