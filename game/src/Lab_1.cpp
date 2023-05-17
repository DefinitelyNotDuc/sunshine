#include "raylib.h"

// InitWindow(800, 600, "Raylib Function Examples") : Initializes a window with the specified width, height, and title.This function is necessary for creating the game window.

// SetTargetFPS(60) : Sets the desired frame rate per second.It ensures that the game loop runs at a consistent frame rate, providing smooth animations and gameplay.

// WindowShouldClose() : Checks if the user has requested to close the window(e.g., clicked the close button).It's used in the loop condition to exit the program when the window is closed.

// GetMousePosition() : Retrieves the current position of the mouse cursor on the screen.We use this function to control the position of the second circle.

// CheckCollisionCircles(circle1Position, circle1Radius, circle2Position, circle2Radius) : Checks if two circles overlap.In our case, we use it to determine if the two circles intersect.

// ClearBackground(RAYWHITE): Clears the screen with the specified color.It's called at the beginning of each frame to reset the screen before drawing.

// BeginDrawing() : Marks the beginning of the rendering process.It prepares the screen for drawing objects and shapes.

// EndDrawing() : Marks the end of the rendering process.It finalizes the rendering and presents the completed frame to the screen.

// DrawCircleV(circle1Position, circle1Radius, circle1Color) : Draws a circle with the specified position, radius, and color.We use this function to render the first circle.

// DrawCircleV(circle2Position, circle2Radius, circle2Color) : Draws the second circle with the specified position, radius, and color.The position of this circle is controlled by the mouse cursor.


            int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Circles");

    // Set up the positions and radii of the two circles
    Vector2 circle1Pos = { screenWidth / 2, screenHeight / 2 };
    float circle1Radius = 50.0f;
    Vector2 circle2Pos = { screenWidth / 2, screenHeight / 2 };
    float circle2Radius = 50.0f;

    while (!WindowShouldClose())
    {
        // Update the position of the second circle based on the mouse cursor position
        circle2Pos = GetMousePosition();

        // Check for collision between the two circles and change their color if they overlap
        if (CheckCollisionCircles(circle1Pos, circle1Radius, circle2Pos, circle2Radius))
        {
            DrawCircle(circle1Pos.x, circle1Pos.y, circle1Radius, RED);
            DrawCircle(circle2Pos.x, circle2Pos.y, circle2Radius, RED);
        }
        else
        {
            DrawCircle(circle1Pos.x, circle1Pos.y, circle1Radius, BLUE);
            DrawCircle(circle2Pos.x, circle2Pos.y, circle2Radius, GREEN);
        }

        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
