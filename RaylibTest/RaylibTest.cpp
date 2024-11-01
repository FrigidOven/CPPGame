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
    scene.AddComponent<Sprite>(testEntity0, 0, &backgroundSprite, Rectangle{ 0, 0, 256, 224 }, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0, 1);

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
    scene.AddComponent<Friction>(testEntity1, 0.8f);
    scene.AddComponent<ForceBasedMovementController>(testEntity1, 1000.0f * IMAGE_SCALE, Input(Keyboard, KEY_UP, true), Input(Keyboard, KEY_LEFT, true), Input(Keyboard, KEY_DOWN, true), Input(Keyboard, KEY_RIGHT, true));
    scene.AddComponent<ForceBasedSpeedLimiter>(testEntity1, 100.0f * IMAGE_SCALE);
    scene.AddComponent<SpriteManager>(testEntity1);

    int testEntity2 = scene.CreateEntity();
    Tag& entityTag2 = scene.GetComponent<Tag>(testEntity2);
    entityTag2.entityGroup = EntityGroup::Player;
    entityTag2.entityType = EntityType::Player;
    entityTag2.direction = Direction::Up;

    scene.AddComponent<Spatial>(testEntity2, Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - (32 * IMAGE_SCALE) / 2 }, 0.0f);
    scene.AddComponent<Sprite>(testEntity2, 1, &golemSprite, Rectangle{ 0, 64, 32, 32 }, 32 * IMAGE_SCALE, 32 * IMAGE_SCALE, 1, 0, 1);
    scene.AddComponent<Velocity>(testEntity2, Vector2Zero());
    scene.AddComponent<VelocityBasedMovementController>(testEntity2, 100.0f * IMAGE_SCALE, Input(Keyboard, KEY_W, true), Input(Keyboard, KEY_A, true), Input(Keyboard, KEY_S, true), Input(Keyboard, KEY_D, true));
    scene.AddComponent<VelocityBasedSpeedLimiter>(testEntity2, 100.0f * IMAGE_SCALE);
    scene.AddComponent<SpriteManager>(testEntity2);

    scene.AddComponent<FollowCamera>(static_cast<int>(SpecialEntities::Camera), testEntity1, Vector2Zero());

    while (!WindowShouldClose())
    {
        game.Update();
    }

    CloseWindow();
    return 0;
}