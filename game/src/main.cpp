#include "raylib.h"
#include <vector>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float AGENT_RADIUS = 10.0f;
const float AGENT_SPEED = 100.0f;
const float AVOIDANCE_FORCE = 200.0f;
const float WHISKER_LENGTH = 50.0f;
const float WHISKER_ANGLE = 30.0f;

struct Agent {
    Vector2 position;
    Vector2 velocity;
    Color color;

    void ObstacleAvoidance(const Vector2& obstaclePosition, float obstacleRadius) {
        Vector2 ahead = position + Vector2Normalize(velocity) * WHISKER_LENGTH;
        Vector2 aheadLeft = RotateVector(Vector2Normalize(velocity), -WHISKER_ANGLE) * WHISKER_LENGTH * 0.8f;
        Vector2 aheadRight = RotateVector(Vector2Normalize(velocity), WHISKER_ANGLE) * WHISKER_LENGTH * 0.8f;

        Vector2 avoidanceForce = { 0, 0 };

        if (CheckCollisionCircleRec(obstaclePosition, obstacleRadius, { ahead.x, ahead.y, 1, 1 })) {
            avoidanceForce += Vector2Normalize(position - obstaclePosition) * AVOIDANCE_FORCE;
        }

        if (CheckCollisionCircleRec(obstaclePosition, obstacleRadius, { aheadLeft.x, aheadLeft.y, 1, 1 })) {
            avoidanceForce += Vector2Normalize(position - obstaclePosition) * AVOIDANCE_FORCE;
        }

        if (CheckCollisionCircleRec(obstaclePosition, obstacleRadius, { aheadRight.x, aheadRight.y, 1, 1 })) {
            avoidanceForce += Vector2Normalize(position - obstaclePosition) * AVOIDANCE_FORCE;
        }

        velocity += avoidanceForce;
    }

    void Update(float deltaTime) {
        position += velocity * deltaTime;
    }

    void Draw() {
        DrawCircleV(position, AGENT_RADIUS, color);
        DrawLineV(position, position + velocity * 5.0f, BLACK);
    }
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Obstacle Avoidance Demo");
    SetTargetFPS(60);

    std::vector<Agent> agents;
    Vector2 mousePosition = { 0, 0 };

    while (!WindowShouldClose()) {
        mousePosition = GetMousePosition();

        // Add new agent if left mouse button is pressed
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Agent newAgent;
            newAgent.position = mousePosition;
            newAgent.velocity = { 1, 0 };
            newAgent.color = GetRandomColor();
            agents.push_back(newAgent);
        }

        // Update agents
        for (Agent& agent : agents) {
            agent.ObstacleAvoidance(mousePosition, 20.0f);
            agent.Update(GetFrameTime());
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw agents
        for (const Agent& agent : agents) {
            agent.Draw();
        }

        // Draw obstacles
        DrawCircleV(mousePosition, 20.0f, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
?
Minchae
Minchae