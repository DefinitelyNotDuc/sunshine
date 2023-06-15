#include "raylib.h"
#include "raymath.h"
#include <vector>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Rigidbody {
public:
    Vector2 position;
    Vector2 velocity;
};

class Sprite {
public:
    Texture2D texture;
    Vector2 position;

    void Draw() {
        DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
    }
};

class Agent {
public:
    Rigidbody rigidbody;
    Sprite sprite;
    float maxSpeed;
    float maxAcceleration;

    Vector2 Seek(const Vector2& targetPos, const float maxAccel) {
        Vector2 desiredVelocity = Vector2Subtract(targetPos, rigidbody.position);
        float distance = Vector2Length(desiredVelocity);

        if (distance > 0) {
            desiredVelocity = Vector2Scale(desiredVelocity, maxSpeed / distance);

            Vector2 steering = Vector2Subtract(desiredVelocity, rigidbody.velocity);
            steering = Vector2Scale(steering, maxAccel / maxSpeed);

            return steering;
        }

        return { 0, 0 };
    }
};

Vector2 WraparoundScreen(const Vector2& position) {
    Vector2 outPosition = {
        fmodf(position.x + SCREEN_WIDTH, SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    std::vector<Agent> agents;
    Agent agent;
    agent.rigidbody.position = { 400, 225 };
    agent.rigidbody.velocity = { 10, 0 };
    agent.maxSpeed = 400.0f;
    agent.maxAcceleration = 800.0f;
    agent.sprite.texture = LoadTexture("Screenshot 2023-06-02 134114.png");
    agents.push_back(agent);

    Rigidbody circleA = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

    while (!WindowShouldClose()) {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t i = 0; i < agents.size(); i++) {
            Agent& agent = agents[i];

            agent.rigidbody.position = WraparoundScreen(agent.rigidbody.position);

            // Seek towards the mouse position while the mouse button is held down
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                Vector2 acceleration = agent.Seek(GetMousePosition(), agent.maxAcceleration);
                agent.rigidbody.velocity = Vector2Add(agent.rigidbody.velocity, acceleration);
            }

            agent.rigidbody.position = Vector2Add(agent.rigidbody.position, Vector2Scale(agent.rigidbody.velocity, deltaTime));
            agent.sprite.position = agent.rigidbody.position;
            agent.sprite.Draw();
        }

        DrawCircleV(circleA.position, 50, RED);

        EndDrawing();
    }

    // Unload resources
    for (size_t i = 0; i < agents.size(); i++) {
        UnloadTexture(agents[i].sprite.texture);
    }

    CloseWindow();

    return 0;
}