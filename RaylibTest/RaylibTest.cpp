#include "Game.h"
#include "GameConstants.h"

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
    scene.AddComponent<Sprite>(testEntity0, 0, &backgroundSprite, Rectangle{ 0, 0, 256, 224 }, 1, 1, 1, 0, 1);

    int testEntity1 = scene.CreateEntity();
    Tag& entityTag1 = scene.GetComponent<Tag>(testEntity1);
    entityTag1.entityGroup = EntityGroup::Player;
    entityTag1.entityType = EntityType::Player;
    entityTag1.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity1, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (32 * PIXEL_SIZE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity1, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 1, 1, 1, 0, 1);
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


    int testEntity2 = scene.CreateEntity();
    Tag& entityTag2 = scene.GetComponent<Tag>(testEntity2);
    entityTag2.entityGroup = EntityGroup::Player;
    entityTag2.entityType = EntityType::Player;
    entityTag2.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity2, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - (32 * PIXEL_SIZE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity2, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 1, 1, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity2, Vector2Zero());
    scene.AddComponent<Controller>(testEntity2,
        Input(ControlType::Keyboard, KEY_UP),
        Input(ControlType::Keyboard, KEY_LEFT),
        Input(ControlType::Keyboard, KEY_DOWN),
        Input(ControlType::Keyboard, KEY_RIGHT));
    scene.AddComponent<MovementController>(testEntity2, MovementMode::VelocityBased, 1.0f);
    scene.AddComponent<SpeedLimiter>(testEntity2, 1.0f);
    scene.AddComponent<SpriteManager>(testEntity2);

    scene.AddComponent<FollowCamera>(static_cast<int>(SpecialEntities::Camera), testEntity0, Vector2Zero());
    
    bool impulseAdded = false;

    while (!WindowShouldClose())
    {
        game.Update();

        if (!impulseAdded && GetTime() > 3.0f)
        {
            impulseAdded = scene.AddComponent<Impulse>(testEntity1, Vector2(50.0f, 0.0f));
        }
    }

    CloseWindow();
    return 0;
}