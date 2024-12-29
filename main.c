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
    Color Teal = {0, 128, 128, 255};
    float posX = 100;
    float posY = 100;
    float radius = 10;
    float push = 5000; // px per frametime
    Vector2 Vel; // initialising the velocity vector
    float coeff_restitution = 0.5;
    float drag_coeff = 0;
    float speed = 0;
    float mass = 1;
    Vector2 accel;
    Vector2 friction; // acceleration due to friction, NOT the frictional force itself
    char string_speed[5]= "";
    float DelT;
    float max_speed = 100;
    InitWindow(screenWidth, screenHeight, "SandSim");
    // InitAudioDevice();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    // Event Handling
        //----------------------------------------------------------------------------------
    
    push = 5000;
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
        friction.x = -drag_coeff*Vel.x*signf(Vel.x);
        friction.y = -drag_coeff*Vel.y*signf(Vel.y);
        //----------------------------------------------------------------------------------
    // Update
        //----------------------------------------------------------------------------------
    Vel = Vector2Add(Vector2Scale(Vector2Add(accel,friction),DelT),Vel);
    posX += Vel.x*DelT;
    posY += Vel.y*DelT;
    accel = Vector2Zero();
    // speed calculation for displaying
    speed = Vector2Length(Vel);

    if (speed>max_speed)
    {
    while (speed>max_speed)
    {
        Vel = Vector2Scale(Vel,0.9);
    }
    }
    
        //----------------------------------------------------------------------------------
    // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(Teal);
            sprintf(string_speed,"%0.2f", speed);
            DrawText(string_speed,0,0,20,BLACK);
            DrawCircle(posX,posY,radius,CLITERAL(Color){ 0, 0, 0, 255 } );
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