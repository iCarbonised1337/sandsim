#include <raylib.h>
#include <stdio.h>
#include <raymath.h>

// Defining functions
int signf(float x) {
    return (x > 0.0f) - (x < 0.0f);
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    float posX = 100;
    float posY = 100;
    float radius = 10;
    float push = 1000; // px per frametime
    float coeff_restitution = 0.5;
    float drag_coeff = 1;
    float speed = 0;
    float mass = 1;
    float DelT;
    Color Teal = {0, 128, 128, 255};
    Vector2 Vel; // initialising the velocity vector
    Vector2 accel;
    Vector2 friction; // acceleration due to friction, NOT the frictional force itself
    char string_speed[5]= "";
    
    //float max_speed = 1000;
    InitWindow(screenWidth, screenHeight, "SandSim");
    // InitAudioDevice();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    // Event Handling
        //----------------------------------------------------------------------------------
    
    DelT = GetFrameTime();
    if (IsKeyDown(KEY_W))
    {
        accel.y = -push/mass;
    }
    if (IsKeyDown(KEY_A))
    {
        accel.x += -push/mass;
    }
    if (IsKeyDown(KEY_S))
    {
        accel.y += push/mass;
    }
    if (IsKeyDown(KEY_D))
    {
        accel.x += push/mass;
    }

    //Check if ball is inside the frame in X and Y seperately
    if ( (posX+(radius)>screenWidth))
    {
        posX += -radius;
        Vel.x-=(1+coeff_restitution)*Vel.x;
    }
    if ((posX < radius))
    {
        posX += radius;
        Vel.x-=(1+coeff_restitution)*Vel.x;
    }
    
    if ((posY+(radius)>screenHeight))
    {
        posY += -radius;
        Vel.y-=(1+coeff_restitution)*Vel.y;
    }
    if ((posY < radius))
    {
        posY += radius;
        Vel.y-=(1+coeff_restitution)*Vel.y;
    }


    // make friction work
        friction.x = -drag_coeff*Vel.x;
        friction.y = -drag_coeff*Vel.y;
        //----------------------------------------------------------------------------------
    // Update
        //----------------------------------------------------------------------------------
    Vel = Vector2Add(Vector2Scale(Vector2Add(accel,friction),DelT),Vel);
    posX += Vel.x*DelT;
    posY += Vel.y*DelT;
    accel = Vector2Zero();
    // speed calculation for displaying
    speed = Vector2Length(Vel);

        //----------------------------------------------------------------------------------
    // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            sprintf(string_speed,"%0.0f", speed);
            DrawText(string_speed,0,0,20,WHITE);
            DrawCircle(posX,posY,radius,Teal);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}