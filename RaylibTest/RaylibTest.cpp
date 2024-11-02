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
    scene.AddComponent<Sprite>(testEntity0, 0, &backgroundSprite, Rectangle{ 0, 0, 256, 224 }, 256 * IMAGE_SCALE, 224 * IMAGE_SCALE, 1, 0, 1);

    int testEntity1 = scene.CreateEntity();
    Tag& entityTag1 = scene.GetComponent<Tag>(testEntity1);
    entityTag1.entityGroup = EntityGroup::Player;
    entityTag1.entityType = EntityType::Player;
    entityTag1.direction = Direction::Down;

    scene.AddComponent<Spatial>(testEntity1, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (32 * IMAGE_SCALE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity1, 1, &golemSprite, Rectangle{ 0, 0, 32, 32 }, 32 * IMAGE_SCALE, 32 * IMAGE_SCALE, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity1, Vector2Zero());
    scene.AddComponent<Acceleration>(testEntity1, Vector2Zero());
    scene.AddComponent<Mass>(testEntity1, 1.0f);
    scene.AddComponent<Force>(testEntity1, Vector2Zero());
    scene.AddComponent<Friction>(testEntity1, 0.9f);
    scene.AddComponent<Controller>(testEntity1, Input(ControlType::Keyboard, KEY_W), Input(ControlType::Keyboard, KEY_A), Input(ControlType::Keyboard, KEY_S), Input(ControlType::Keyboard, KEY_D));
    scene.AddComponent<MovementController>(testEntity1, MovementMode::ForceBased, 1000.0f * IMAGE_SCALE);
    scene.AddComponent<SpeedLimiter>(testEntity1, 100.0f * IMAGE_SCALE);
    scene.AddComponent<SpriteManager>(testEntity1);

    int testEntity2 = scene.CreateEntity();
    Tag& entityTag2 = scene.GetComponent<Tag>(testEntity2);
    entityTag2.entityGroup = EntityGroup::Player;
    entityTag2.entityType = EntityType::Player;
    entityTag2.direction = Direction::Up;

    scene.AddComponent<Spatial>(testEntity2, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - (32 * IMAGE_SCALE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity2, 1, &golemSprite, Rectangle{ 0, 64, 32, 32 }, 32 * IMAGE_SCALE, 32 * IMAGE_SCALE, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity2, Vector2Zero());
    scene.AddComponent<Controller>(testEntity2, Input(ControlType::Keyboard, KEY_UP), Input(ControlType::Keyboard, KEY_LEFT), Input(ControlType::Keyboard, KEY_DOWN), Input(ControlType::Keyboard, KEY_RIGHT));
    scene.AddComponent<MovementController>(testEntity2, MovementMode::VelocityBased, 1000.0f * IMAGE_SCALE);
    scene.AddComponent<SpeedLimiter>(testEntity2, 100.0f * IMAGE_SCALE);
    scene.AddComponent<SpriteManager>(testEntity2);

    scene.AddComponent<FollowCamera>(static_cast<int>(SpecialEntities::Camera), testEntity1, Vector2Zero());

    while (!WindowShouldClose())
    {
        game.Update();
    }

    CloseWindow();
    return 0;
}