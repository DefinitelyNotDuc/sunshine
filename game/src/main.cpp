#include <raylib.h>
#include <vector>

class Rigidbody {
public:
    Vector2 position;
    Vector2 velocity;
};

class Agent {
public:
    Rigidbody rigidbody;
    Texture2D sprite;
    float maxSpeed;
    float maxAcceleration;
};

void UpdateRigidbody(Rigidbody& rigidbody, float deltaTime) {
    rigidbody.position += rigidbody.velocity * deltaTime;
}

Vector2 Seek(Vector2 agentPosition, Vector2 agentVelocity, Vector2 targetPosition, float maxAcceleration) {
    Vector2 desiredVelocity = Vector2Normalize(targetPosition - agentPosition) * Vector2Length(agentVelocity);
    Vector2 steering = desiredVelocity - agentVelocity;
    return Vector2Clamp(steering, -maxAcceleration, maxAcceleration);
}

Vector2 Flee(Vector2 agentPosition, Vector2 agentVelocity, Vector2 targetPosition, float maxAcceleration) {
    Vector2 desiredVelocity = Vector2Normalize(agentPosition - targetPosition) * Vector2Length(agentVelocity);
    Vector2 steering = desiredVelocity - agentVelocity;
    return Vector2Clamp(steering, -maxAcceleration, maxAcceleration);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Kinematics Simulation");
    SetTargetFPS(60);

    std::vector<Agent> agents;
    Agent agent1;
    agent1.rigidbody.position = { 100, 200 };
    agent1.rigidbody.velocity = { 100, 0 };
    agent1.maxSpeed = 200.0f;
    agent1.maxAcceleration = 100.0f;
    agent1.sprite = LoadTexture("agent1.png");
    agents.push_back(agent1);

    Agent agent2;
    agent2.rigidbody.position = { 500, 200 };
    agent2.rigidbody.velocity = { -100, 0 };
    agent2.maxSpeed = 150.0f;
    agent2.maxAcceleration = 80.0f;
    agent2.sprite = LoadTexture("agent2.png");
    agents.push_back(agent2);

    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        for (auto& agent : agents) {
            Vector2 targetPosition = GetMousePosition();

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                Vector2 acceleration = Seek(agent.rigidbody.position, agent.rigidbody.velocity, targetPosition, agent.maxAcceleration);
                agent.rigidbody.velocity += acceleration * deltaTime;
            }

            UpdateRigidbody(agent.rigidbody, deltaTime);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& agent : agents) {
            DrawTexture(agent.sprite, agent.rigidbody.position.x, agent.rigidbody.position.y, WHITE);
        }

        EndDrawing();
    }

    for (const auto& agent : agents) {
        UnloadTexture(agent.sprite);
    }

    CloseWindow();

    return 0;
}