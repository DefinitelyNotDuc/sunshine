#include "raylib.h"
#include <iostream>
#include <vector>

const int TILE_SIZE = 50; // Size of each tile
const int GRID_WIDTH = 10; // Number of tiles in the grid (width)
const int GRID_HEIGHT = 6; // Number of tiles in the grid (height)

struct Tile {
    Vector2 position; // Position of the tile in the grid
    bool isFloor; // Whether the tile is a floor tile or not
};

void DrawAdjacency(const Tile& tile1, const Tile& tile2) {
    Vector2 center1 = { tile1.position.x + TILE_SIZE / 2, tile1.position.y + TILE_SIZE / 2 };
    Vector2 center2 = { tile2.position.x + TILE_SIZE / 2, tile2.position.y + TILE_SIZE / 2 };
    DrawLineEx(center1, center2, 2, GREEN);
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

int main() {
    const int screenWidth = GRID_WIDTH * TILE_SIZE;
    const int screenHeight = GRID_HEIGHT * TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "Tile Adjacency");

    std::vector<Tile> tiles;
    std::vector<Vector2> floorTilePositions;
    std::vector<std::vector<bool>> adjacencyMatrix(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            Tile tile;
            tile.position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };
            tile.isFloor = true;
            tiles.push_back(tile);
            floorTilePositions.push_back(tile.position);
        }
    }

    SetTargetFPS(60);

    Vector2 characterPosition = { 0, 0 };

    while (!WindowShouldClose()) {
        // Character movement
        Vector2 movement = { 0, 0 };
        if (IsKeyDown(KEY_W)) {
            movement.y -= 1;
        }
        if (IsKeyDown(KEY_A)) {
            movement.x -= 1;
        }
        if (IsKeyDown(KEY_S)) {
            movement.y += 1;
        }
        if (IsKeyDown(KEY_D)) {
            movement.x += 1;
        }

        Vector2 newPosition = characterPosition + movement;
        if (newPosition.x >= 0 && newPosition.x < screenWidth && newPosition.y >= 0 && newPosition.y < screenHeight) {
            int tileIndex = newPosition.y / TILE_SIZE * GRID_WIDTH + newPosition.x / TILE_SIZE;
            if (tiles[tileIndex].isFloor) {
                characterPosition = newPosition;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw adjacency lines
        for (const Tile& tile : tiles) {
            if (tile.isFloor) {
                int tileIndex = tile.position.y / TILE_SIZE * GRID_WIDTH + tile.position.x / TILE_SIZE;
                if (tile.position.x < (GRID_WIDTH - 1) * TILE_SIZE && tiles[tileIndex + 1].isFloor) {
                    DrawAdjacency(tile, tiles[tileIndex + 1]);
                }
                if (tile.position.y < (GRID_HEIGHT - 1) * TILE_SIZE && tiles[tileIndex + GRID_WIDTH].isFloor) {
                    DrawAdjacency(tile, tiles[tileIndex + GRID_WIDTH]);
                }
            }

            DrawCircle(tile.position.x + TILE_SIZE / 2, tile.position.y + TILE_SIZE / 2, TILE_SIZE / 4, GREEN);
        }

        // Draw the character sprite
        DrawRectangle(characterPosition.x, characterPosition.y, TILE_SIZE, TILE_SIZE, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}