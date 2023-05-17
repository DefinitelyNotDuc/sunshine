#include "raylib.h"


// This function initializes a window with the specified width and height. It's useful because it sets up the basic window infrastructure required to render graphics.
// InitWindow(640, 480, "My Window");

// This function sets the target frame rate for the application. It's useful because it can help to smooth out animations and make the application feel more responsive.
// SetTargetFPS(60);

// This function sets up the rendering environment for the current frame. It's useful because it allows you to draw multiple graphics primitives within the same frame.
// BeginDrawing();

// This function draws a string of text on the screen at the specified coordinates. It's useful for displaying information or user interfaces.
// DrawText("Hello, world!", 100, 100, 20, BLACK);

// This function draws a rectangle on the screen at the specified coordinates and with the specified dimensions. It's useful for drawing shapes and backgrounds.
// DrawRectangle(200, 200, 50, 50, BLUE);

// This function loads an image from file into a texture. It's useful for creating custom graphics assets.
// Texture myTexture = LoadTexture("my_texture.png");

// This function releases the memory used by a texture. It's useful for managing resources and avoiding memory leaks.
// UnloadTexture(myTexture);

// This function checks whether a key is currently pressed. It's useful for implementing keyboard-based controls.
// if (IsKeyDown(KEY_SPACE)) {
    // do something
// }

//  This function sets the position of the mouse cursor. It's useful for implementing custom mouse-based controls.
// SetMousePosition(100, 100);

// This function returns a random integer value between two specified values. It's useful for implementing random events or generating random game objects.
// int myRandomValue = GetRandomValue(1, 10);


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
